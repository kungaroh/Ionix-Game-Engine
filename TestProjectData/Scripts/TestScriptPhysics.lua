TestScriptPhysics = 
{
uid = 2,
graveScale = 2.5,
forceX = 2.5,
forceY = 3.5,
forcePosX = 4.5,
forcePosY = 5.5,
posX = 6.5, 
posY =7.5, 
w =8.5, 
h =9.5, 
isTrigger = true,
radius = 10.5,
ID = 11.5,
}
function TestScriptPhysics:OnStart()
        print ("Physics Started")
end
-----------------------------------------------------------------------------------------------------------------------------------
function TestScriptPhysics:OnUpdate( deltaTime)
    if is_key_down("Ionix_B")   then 
        set_gravity_scale(self.graveScale) 
        print ("Gravity scaled On Update")
    end 
-----------------------------------------------------------------------------------------------------------------------------------
    if deltaTime > 400 then 
        add_force(self.foreceX,self.forceY,slef.forcePosX,slef.forcePosY)
        print ("Force added on update")
    end

-----------------------------------------------------------------------------------------------------------------------------------
    if deltaTime > 600 then 
        add_box_collider(self.posX,self.posY,self.w,self.h,self.isTrigger)
        print ("Box collider set on update")
    end
-----------------------------------------------------------------------------------------------------------------------------------
    if deltaTime > 700 then
    add_circle_collider(self.posX,self.posY,self.radius,self.isTrigger)
        print ("Circle collider added on update")
    end
-----------------------------------------------------------------------------------------------------------------------------------
if deltaTime > 900 then
    remove_collider(self.ID)
        print ("Collider removved onUpdate")
    end
-----------------------------------------------------------------------------------------------------------------------------------
end

