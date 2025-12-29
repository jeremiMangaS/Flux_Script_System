print("Message from LUA")

-- function on_update(motion)
--     drawText("Draw Text System", 20, 40, 0.6, 0, 255, 0)
--     -- Print in the camera tab
--     drawText("Motion : " .. math.floor(motion), 20, 110, 0.6, 255, 255, 0)
--     if motion > 0 then
--         print("Moving object detected : " .. motion);
--         drawText("MOVE DETECTED", 20, 80, 0.8, 255, 0, 0)
--     end

--     drawRect(detX, detY, detW, detH, 255, 0, 0);
--     drawText("OBJECT", detX, detY - 10, 0.5, 255, 0, 0);
-- end


-- function on_update(motion)
--     drawText("MULTI OBJEC TESTING", 20, 40, 0.6, 255, 255, 255)
--     if detected_list then 
--         for i, obj in ipairs(detected_list) do 
--             drawRect(obj.x, obj.y, obj.w, obj.h, 255, 0, 0)
--             drawText("ID : " .. i, obj.x, obj.y - 10, 0.4, 255, 255, 0)
--         end
--     end
-- end


function on_update(motion)
    drawText("FACE RECOGNIZE", 20, 40, 0.6, 255, 255, 255)
    
    if detected_list ~= nil then 
        for i, obj in ipairs(detected_list) do 
            drawRect(obj.x, obj.y, obj.w, obj.h, 255, 0, 0)
            drawText("ID : " .. i, obj.x, obj.y - 10, 0.4, 255, 255, 0)
        end
    end

    if face_lists ~= nil then 
        for i, face in ipairs(face_lists) do 
            drawRect(face.x, face.y, face.w, face.h, 0, 255, 255)
            drawText("FACE DETECTED", face.x, face.y - 10, 0.5, 0, 255, 255)
        end
    end

end