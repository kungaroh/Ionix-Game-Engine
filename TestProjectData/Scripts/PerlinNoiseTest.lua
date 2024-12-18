PerlinNoiseTest = 
{
lineHeight = 30,
lineWidth = 93,
cellSize = 5,
position = newVector2(RandomRangeInt(1,300),RandomRangeInt(1,300))
}

function PerlinNoiseTest:OnStart ()
    log("Start Perlin Noise Test")
end

function PerlinNoiseTest:OnUpdate (deltaTime)

    self.position.y = self.position.y+self.lineHeight
    self.cellSize = self.cellSize+1

    --[[
    for y = 1, self.lineHeight do
        local animation = ""
        for x = 1, math.abs(self.lineWidth) do
            
        animation = animation .. RoundToInt(9*PerlinNoise(self.position.x+x,self.position.y+y,self.cellSize))
        
    end
    log(animation)
    end  
    ]]

   for y = 1, self.lineHeight do

        local animation = ""

        for x = 1, math.abs(self.lineWidth) do

            if PerlinNoise(self.position.x+x,self.position.y+y,self.cellSize)>0.5 then

                animation = animation .. RoundToInt(9*PerlinNoise(self.position.x+x,self.position.y+y,self.cellSize))
            else

                animation = animation .. " "
            end
        
        end

        log(animation)
    end

end
