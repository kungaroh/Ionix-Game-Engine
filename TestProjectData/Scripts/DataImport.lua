DataImport = {



}


function DataImport:importData()
--use loadfile or dofile to loop through 
local data = loadfile(sandbox)
if data ~= nil then return "error"
end