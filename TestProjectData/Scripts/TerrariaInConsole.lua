TerrariaInConsole = 
{
    lineHeight = 30,
lineWidth = 93,
textSpace = 27,
Location = newVector2(RandomRangeInt(1000,5000),RandomRangeInt(900,1500)),
cellSize = 5,
noiseBound = 0.55
}
function TerrariaInConsole:OnStart ()
    self.cellSize = RandomRangeInt(1,9)
    log("Start TerrariaInConsole")
end

function TerrariaInConsole:OnUpdate (deltaTime)

    if is_key_held("Ionix_W") and PerlinNoise(self.Location.x+FloorToInt((self.lineWidth+self.textSpace)/2),self.Location.y+FloorToInt(self.lineHeight/2)-1,self.cellSize)<self.noiseBound then 
        self.Location.y = self.Location.y-1
    end
    if is_key_held("Ionix_A") and PerlinNoise(self.Location.x+FloorToInt((self.lineWidth+self.textSpace)/2)-1,self.Location.y+FloorToInt(self.lineHeight/2),self.cellSize)<self.noiseBound then
        self.Location.x = self.Location.x-1
    end
    if is_key_held("Ionix_S") and PerlinNoise(self.Location.x+FloorToInt((self.lineWidth+self.textSpace)/2),self.Location.y+FloorToInt(self.lineHeight/2)+1,self.cellSize)<self.noiseBound then 
        self.Location.y = self.Location.y+1
    end
    if is_key_held("Ionix_D") and PerlinNoise(self.Location.x+FloorToInt((self.lineWidth+self.textSpace)/2)+1,self.Location.y+FloorToInt(self.lineHeight/2),self.cellSize)<self.noiseBound then 
        self.Location.x = self.Location.x+1
    end
    
    local animation = ""
    for y = 1, math.abs(self.lineWidth) do
        animation = animation .. " "
    end

    for y = 1, math.abs(self.lineHeight) do
        for x = 1, math.abs(self.lineWidth+self.textSpace) do
            if y == FloorToInt(self.lineHeight/2) and x == FloorToInt((self.lineWidth+self.textSpace)/2) then
                animation = animation .. "&"
            elseif PerlinNoise(self.Location.x+x,self.Location.y+y,self.cellSize)>self.noiseBound then
                animation = animation .. RoundToInt(self.cellSize)
                --animation = animation .. RoundToInt(9*PerlinNoise(self.Location.x+x,self.Location.y+y,self.cellSize))
            else

                animation = animation .. " "
            end
        end
    end

  
    log(animation)
    

end
