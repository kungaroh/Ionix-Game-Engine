BallAnimation = 
{
    lineHeight = 30,
lineWidth = 93,
textSpace = 27,
Location = newVector2(45,15),
Direction = newVector2(1,1)
}

function BallAnimation:OnStart ()
    log("Start Ball Animation")
end

function BallAnimation:OnUpdate (deltaTime)

    if self.Location.x > self.lineWidth+self.textSpace-7 or self.Location.x < 1 then
        self.Direction.x = -self.Direction.x
    end
    if self.Location.y > self.lineHeight or self.Location.y < 4 then
        self.Direction.y = -self.Direction.y
    end
    
    if self.Location.x<(self.lineWidth+self.textSpace*2)/3 and self.Location.x>(self.lineWidth+self.textSpace)/3 and self.Location.y<(self.lineHeight*2)/3 and self.Location.y>(self.lineHeight)/3 then
self.Direction:Set(RandomRangeInt(-1,2),RandomRangeInt(-2,1))
    end


    self.Location:add(self.Direction)

    local animation = ""
    local spaces = self.textSpace
    for y = 1, math.abs(self.lineWidth) do
        animation = animation .. " "
        spaces = spaces+1
        end

    for y = 1, math.abs(self.Location.y) do
        for x = 1, math.abs(self.lineWidth+self.textSpace) do
        animation = animation .. " "
        spaces = spaces+1
        end
    end
    for x = 1, math.abs(self.Location.x) do
        animation = animation .. " "
        spaces = spaces+1
    end
    animation = animation.."("..RoundToInt(self.Direction.x)..":"..RoundToInt(self.Direction.y)..")"
    for x = spaces-4, math.abs((self.lineWidth+self.textSpace)*self.lineHeight) do
        animation = animation .. " "
    end

    

    --log(animation)
end
