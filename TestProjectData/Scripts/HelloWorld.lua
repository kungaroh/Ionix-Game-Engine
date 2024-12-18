HelloWorld = 
{
    test = 0,
  vec1 = newVector2(3,6),
  vec2 = newVector2(12,9),
  ballDir = 1,
  ballpos = 5
}

function HelloWorld:OnStart ()
    log("Start Hello World")
end

function HelloWorld:OnUpdate (deltaTime)
    --Don't forget "self" to access variables
    log("----------------------------------------------------------------------------------------------------------------------------------------")
    log("runtime: "..self.test)
    log("deltaTime: "..deltaTime)
    self.test = self.test+deltaTime
    print("vec1: (" .. self.vec1.x .. " , " .. self.vec1.y .. ") Magnitude: " .. self.vec1.magnitude)
    print("vec2: (" .. self.vec2.x .. " , " .. self.vec2.y .. ") Magnitude: " ..  self.vec2.magnitude)
    self.vec1.x = self.vec1.x+1
    self.vec1.y = self.vec1.y-1
    self.vec2.x = self.vec2.x+2
    self.vec2.y = self.vec2.y+1

    if self.ballpos > 50 or self.ballpos < 1 then
        self.ballDir = -self.ballDir
    end
    self.ballpos = self.ballpos + self.ballDir
    local animation = ""
    for x = 1, math.abs(self.ballpos) do
        animation = animation .. " "
    end
    animation = animation .. "O"
    
    log_warning(animation)
    log_error("53.6 rounded to int = "..RoundToInt(53.6))
    log_warning("3.4 rounded to int = "..RoundToInt(3.4))
    log_error("94^23 "..PowerOf(94,23))
    --Call_Function("HelloWorld",":numbers("..deltaTime..")",deltaTime)
end

function HelloWorld:numbers(x)
    log("number: "..x)
    log("Test: "..self.test)
end