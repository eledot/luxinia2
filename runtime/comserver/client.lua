local settings = select(1,...) or {port = "55555"}

do
	local zmq = require "zmq"
	local ctx = zmq.init(1)
	local s = ctx:socket(zmq.REQ)
	local addr = "tcp://127.0.0.1:"..settings.port
	
	print("client:",addr)
	if (not s:connect(addr)) then 
			print("client: failed")
		return 
	end

	LXG = LXG or {}
	LXG.clientsend = function(msg)
		s:send(msg)
		if (s:recv() ~= "OK") then
			print("error: could not send",msg)
		end
	end
end