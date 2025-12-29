print("Message from LUA")

function on_update(motion)
    drawText("Draw Text System", 20, 40, 0.6, 0, 255, 0)
    -- Print in the camera tab
    drawText("Motion : " .. math.floor(motion), 20, 110, 0.6, 255, 255, 0)
    if motion > 0 then
        print("Moving object detected : " .. motion);
        drawText("MOVE DETECTED", 20, 80, 0.8, 255, 0, 0)
    end

    drawRect(detX, detY, detW, detH, 255, 0, 0);
    drawText("OBJECT", detX, detY - 10, 0.5, 255, 0, 0);
end
