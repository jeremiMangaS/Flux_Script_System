print("Message from LUA")

local motion = current_motion or 0

if motion > 5000 then
    print("Capture a movement");
end
