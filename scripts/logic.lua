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


-- function on_update(motion)
--     drawText("FACE RECOGNIZE", 20, 40, 0.6, 255, 255, 255)

--     if detected_list ~= nil then
--         for i, obj in ipairs(detected_list) do
--             drawRect(obj.x, obj.y, obj.w, obj.h, 255, 0, 0)
--             drawText("ID : " .. i, obj.x, obj.y - 10, 0.4, 255, 255, 0)
--         end
--     end

--     if face_lists ~= nil then
--         for i, face in ipairs(face_lists) do
--             drawRect(face.x, face.y, face.w, face.h, 0, 255, 255)
--             drawText("FACE DETECTED", face.x, face.y - 10, 0.5, 0, 255, 255)
--         end
--     end

-- end





-- SECURITY SYSTEM
local security_zone = { x = 400, y = 100, w = 200, h = 300 } -- x y w h
local laast_captured_time = 0
local capture_delay = 2
local detect_time = 0
local wait_to_capture = false
function is_touching(object, zone)
    return object.x < zone.x + zone.w and object.x + object.w > zone.x and object.y < zone.y + zone.h and
    object.y + object.h > zone.y
end

function on_update(motion)
    local is_alarm_active = false
    local currentTime = os.time()
    drawText("SECURITY SYSTEM", 20, 40, 0.6, 255, 255, 255)
    drawRect(security_zone.x, security_zone.y, security_zone.w, security_zone.h, 255, 255, 255)
    drawText("SECURITY_LINE", security_zone.x + 5, security_zone.y + 25, 0.5, 255, 255, 255)
    if detected_list then
        for i, obj in ipairs(detected_list) do
            if is_touching(obj, security_zone) then
                is_alarm_active = true
                drawRect(obj.x, obj.y, obj.w, obj.h, 0, 0, 255)
                drawText("INTRUDER!!!", obj.x, obj.y - 10, 0.5, 0, 0, 255)
                if not wait_to_capture then 
                    detect_time = currentTime
                    wait_to_capture = true 
                else
                    if (currentTime - laast_captured_time) >= capture_delay then
                        local filename = "intruder_" .. currentTime .. ".jpg"
                        saveImg(filename)
                        laast_captured_time = currentTime
                        print("LUA SYSTEM : Photo taken : " .. filename)
                    end
                end
            else
                drawRect(obj.x, obj.y, obj.w, obj.h, 0, 255, 0)
            end
        end
    end
    if not is_alarm_active then 
        wait_to_capture = false
    end
    if is_alarm_active then
        drawText("WARNING : A VIOLATION OCCURRED!!!", 150, 450, 1.0, 0, 0, 255)
        if wait_to_capture and (currentTime - laast_captured_time >= capture_delay) then 
            drawText("CAPTURING...", 400, 80, 0.4, 0, 255, 255)
        end
    end

    draw_gui(motion)
end

function draw_gui(motion)
    local sidebarX = 640

    drawRect(sidebarX, 0, 200, 480, 50, 50, 50) -- background
    drawText("PANEL >> ", sidebarX + 10, 30, 0.5, 255, 255, 255)
    drawText("MOTION : " .. math.floor(motion), sidebarX + 10, 70, 0.4, 200, 200, 200)
    if is_alarm_active then 
        drawRect(sidebarX + 10, 100, 100, 40, 0, 0, 150)
        drawText("SYSTEM SEND : ALERT !!! ", sidebarX + 20, 125, 0.4, 255, 255, 255)
    else 
        drawRect(sidebarX + 10, 100, 180, 40, 0, 150, 0)
        drawText("SYSTEM SEND : SECURE ", sidebarX + 20, 125, 0.4, 255, 255, 255)
    end

    drawText("LOGS : ", sidebarX + 10, 200, 0.4, 255, 255, 0)
    drawText("CAMERA : ACTIVE ", sidebarX + 10, 230, 0.3, 150, 150, 150)
    drawText("ZONE : ", sidebarX + 10, 250, 0.3, 150, 150, 150)
end
