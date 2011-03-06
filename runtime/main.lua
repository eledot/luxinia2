do
	LXG = LXG or {}

	local function luafilename(level)
		level = level and level + 1 or 2
		local src
		while (true) do
			src = debug.getinfo(level)
			if (src == nil) then return nil,level end
			if (string.byte(src.source) == string.byte("@")) then
				return string.sub(src.source,2),level
			end
			level = level + 1
		end
	end

	local function luafilepath(level)
		local src,level = luafilename(level)
		if (src == nil) then return src,level end
		src = string.gsub(src,"[\\/][^\\//]*$","")
		return src,level
	end
	
	local function relativeFilename(file)
		assert(type(file)=='string',"String as filename expected")
		local name = file
		local level = 3
		while (name) do
			local found = false
			local fp = io.open(name,"rb")
			if fp then
				fp:close()
				found = true
			end
			if (found) then return name end
			name,level = luafilepath(level)
			if (name == nil) then break end
			name = name .. "/" .. file
		end
		
		return file
	end
	
	local function relativeFilepath(file)
		local name,level = luafilepath(3)
		return (file and name) and name.."/"..file or file or name
	end
	
	-----------------------------
	
	LXG.relpath = relativeFilepath
	LXG.relfile = relativeFilename
	
	-----------------------------
	
	local _loadfile = loadfile
	loadfile = function (file)
		assert(type(file)=='string',"String as filename expected")
		local name = relativeFilename(file)
		
		return _loadfile(name)
	end
	dofile = function (file, ...)
		assert(type(file) == 'string',"String as filename expected")
		local fn,err = loadfile(file)
		local args = {...}
		if not fn then
			print("Error: "..err)
		else
			xpcall(function() return fn(unpack(args)) end,function(err)
				print(debug.traceback(err))
			end)
		end
	end
	
	-----------------------------

	local p = relativeFilepath "clibs_"..jit.os.."_"..jit.arch
	local l = relativeFilepath "lua"
	local s = jit.os == "Windows" and ".dll" or ".so"
	local cstr = string.format(";%s/?%s;%s/?51%s;%s/?/?%s;%s/?/?51%s;",p,s,p,s,p,s,p,s)
	local lstr = string.format(";%s/?.lua;%s/?/?.lua;%s/?/init.lua;",p,p,p)
	package.path  = package.path..lstr
	package.cpath = package.cpath..cstr
	
	------------------------------
	
	local ffi = require("ffi")
	ffi.cdef[[
	void Sleep(int ms);
	int poll(struct pollfd *fds, unsigned long nfds, int timeout);
	]]

	local sleep
	if ffi.os == "Windows" then
		function sleep(s)
			ffi.C.Sleep(s)
		end
	else
		function sleep(s)
			ffi.C.poll(nil, 0, s)
		end
	end
	
	LXG.sleep = sleep
	
end

local args = {...}
local argcnt = #args
local i = 1
local svSetting
while (i <= argcnt) do
	local v = args[i]
	if (v == "-sp" or v == "--serverport") then
		i = i + 1
		local port = args[i]
		assert(tonumber(port),"no port defined")
		svSetting = svSetting or {}
		svSetting.port = port
	elseif (v == "-s" or v == "--server") then
		dofile("comserver/server.lua",svSetting)
	else
		dofile(v)
	end
	i = i + 1
end

if (LXG.serverpoll) then
	local serverpoll = LXG.serverpoll
	local sleep = LXG.sleep
	while(true) do
		serverpoll()
		sleep(10)
	end
end

