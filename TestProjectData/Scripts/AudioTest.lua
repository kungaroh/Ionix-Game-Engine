AudioTest = 
{
audioFile = ("D://GameEngines24-25//TestProjectData//Audio//Music.WAV"),
loopCount = -1,
minRandom = 60,
maxRandom = 720,
handle = 0,
time = 0
}

function AudioTest:OnStart()
    self.handle = play_audio(self.audioFile, self.loopCount)
    print (self.handle)
end
------------------------------------------------------------------------
function AudioTest:OnUpdate( deltaTime )
    if is_key_down("Ionix_Up")  then
        pause_audio (self.handle)
        print ("Audio Paused")
    end
    if is_key_down("Ionix_Down")  then
        resume_audio (self.handle)
        print ("Audio Resumed")
    end
    if  is_key_down("Ionix_Left")  then
        set_volume(50, self.handle)
        print ("Set Volume")--set audio 50%
    end

    if self.time > 60  then
        fade_in (3,self.handle)
        print ("Fade In")--3ms fade in

    if self.time > 75  then
        fade_out(3,self.handle)
        print ("Fade Out") -- 3ms fade out
    end

    if self.time > 90  then
        timed_play(self.handle,120)
        print ("Timed play")
    end

    if self.time > 105  then
        random_timed_play(self.handle, minInterval, maxInterval)
    end
end







    

 
  

end
