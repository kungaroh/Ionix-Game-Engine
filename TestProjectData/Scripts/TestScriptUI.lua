UIELEMENT_ID = 0 
TestScriptUI = 
{
x = 100,
y = 100,
givenID = 2,
UIELEMENT_ID = UIELEMENT_ID + 1,
groupID =  UIELEMENT_ID + 1,
ID = 2,
sizeX = 20,
sizeY = 20,
text = "Help"
}
function TestScriptUI:OnStart()
        print ("On Start Label Pressed")
end
-----------------------------------------------------------------------------------------------------------------------------------
function TestScriptUI:OnUpdate( deltaTime)
    if is_key_down("Ionix_B")   then 
        add_button(self.text, self.x, self.y, self.sizeX, self.sizeY, self.givenID,self.groupID) 
        print ("On update button added")
    end 
-----------------------------------------------------------------------------------------------------------------------------------
    if deltaTime > 400 then 
        add_label(self.text, self.x, self.y, self.givenID, self.groupID)
        print ("Label Added")
    end

-----------------------------------------------------------------------------------------------------------------------------------
    if deltaTime > 600 then 
        set_group_position(self.ID, self.x, self.y)
        print ("Group poition Set")
    end
-----------------------------------------------------------------------------------------------------------------------------------
    if deltaTime > 700 then
    get_button_pressed(self.ID)
        print ("Button pressed")
    end
-----------------------------------------------------------------------------------------------------------------------------------
end

