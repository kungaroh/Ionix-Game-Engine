InputTest = 
{

}

function InputTest:OnStart()
end

function InputTest:OnUpdate( deltaTime )
    if is_key_down("Ionix_B") then 
        print ("B")
    end

    if is_key_held("Ionix_F") then
        log("F")
    end

    if is_key_up("Ionix_U") then
        log("U")
    end
-----------------------Mouse Down-----------------------
    if is_mouse_down("Ionix_LeftClick") then 
        log("Left Click Down")
    end
    if is_mouse_down("Ionix_RightClick") then 
        log("Right Click Down")
    end
    if is_mouse_down("Ionix_MiddleClick") then 
        log("Middle Click Down")
    end
-----------------------Mouse Held-----------------------
    if is_mouse_held("Ionix_LeftClick") then 
        log("Left Click Held")
    end
    if is_mouse_held("Ionix_RightClick") then 
        log("Right Click Held")
    end
    if is_mouse_held("Ionix_MiddleClick") then 
        log("Middle Click Held")
    end
    -----------------------Mouse Up-----------------------
    if is_mouse_up("Ionix_LeftClick") then 
        log("Left Click Up")
    end
    if is_mouse_up("Ionix_RightClick") then 
        log("Right Click Up")
    end
    if is_mouse_up("Ionix_MiddleClick") then 
        log("Middle Click Up")
    end
    -----------------------Get Mouse Position-----------------------
    local mouseX = get_mouse_x() 
    
    
    log("Mouse X position: " .. mouseX)

    local mouseY = get_mouse_y() 
    
    
    log("Mouse Y position: " .. mouseY)

end
