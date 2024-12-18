-- basic format is to include serializable variables in the table at the top.
-- Object name should be the same as the file name.
-- This object will be cloned - a 'new' function will be added to it at load time
TestScript = 
{
    -- add initial variables here
    x = 100, y = 100, xspeed = 100, yspeed = 100, mouseX = 0, mouseY = 0
}

function TestScript.OnStart(self)
    self.x, self.y = get_object_position(self._gameObjUID)
end

function TestScript.OnUpdate(self, deltaTime)
    -- do update here
    --self.x = self.x + deltaTime * self.xspeed
    --self.y = self.y + deltaTime * self.yspeed
    -- set transform using object id 
    -- set_object_position(self._gameObjUID, self.x, self.y)
    
    -- INPUT EXAMPLES --
    
    self:CheckSpaceBarHeld()
    self:CheckSpaceBarPressed()
    
	self:CheckRightMouseButton()
    self:CheckLeftMouseButton()
    self:CheckMiddleMouseButton()
	
	if Ionix_Button("Test button", 10, 10, 100, 50) then
		print("Button clicked!")
	end
	
	if Ionix_Button("Test button 2", 250, 250, 100, 100) then
		print("Button clicked!")
	end
end

function TestScript:CheckSpaceBarHeld()
    if is_key_held(IONIX_SPACE) then
        print("Spacebar is being held down.")
    end
end

function TestScript:CheckSpaceBarPressed()
    if is_key_pressed(IONIX_SPACE) then
        print("Spacebar was pressed once.")
    end
end

function TestScript:CheckLeftMouseButton()
    if is_mouse_button_pressed(MOUSE_BUTTON_LEFT) then
        print("Left mouse button pressed.")
    end
end

function TestScript:CheckRightMouseButton()
    if is_mouse_button_pressed(MOUSE_BUTTON_RIGHT) then
        print("Right mouse button pressed.")
    end
end

function TestScript:CheckMiddleMouseButton()
    if is_mouse_button_pressed(MOUSE_BUTTON_MIDDLE) then
        print("Middle mouse button pressed.")
    end
end

function TestScript:PrintMousePosition()
    local mouseX, mouseY = get_mouse_position()
    print(mouseX .. " " .. mouseY)
end