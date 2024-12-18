let fileDir = '';
let exportFileDir = '';
let gameProcess = null;
let openAsset = '';

//LAYERS
let layerBackground = new TileLayer('layerBackground');
let layerDecoration = new TileLayer('layerDecoration');	
let layerStatic = new TileLayer('layerStatic');
let layerObjects = new ObjectGroup('layerObjects');
let layerUI = new ObjectGroup('layerUI');


fileDir = fileDir.concat(tiled.applicationDirPath.replace('TiledEditor/Tiled-2024.10.31_Windows-10+_x86_64',''), 'bin/Debug-x86_64-windows/Client/Client.exe');
exportFileDir = exportFileDir.concat(tiled.applicationDirPath.replace('TiledEditor/Tiled-2024.10.31_Windows-10+_x86_64',''), 'GameEngineTileMap/Lua');

//----------------------------------------------------

let launchEngine = tiled.registerAction("LaunchExecutable", function(action){
	
	//the file directory of the Client.exe is hardcoded, DO NOT RENAME.
	
	const exectuablePath = fileDir;
	//change filepath to "C:/GameEngines24-25/bin/Debug-x86_64-windows/Client/Client.exe" for release
	
	//tiled.log(tiled.actions); debug print

	
	//---EXPORT TILEMAP AND TILESET---
	tiled.alert("Export the map as GameEngineTileMap.lua, into directory:\n\n" + exportFileDir);
	tiled.trigger("ExportAs");


	//---LAUNCH GAME---
	gameProcess = new Process();
	
	if (!gameProcess.start(exectuablePath)){
		tiled.alert("Failed to find Client.exe in path\n\n" + exectuablePath);
		gameProcess = null;
		return;
	}
	console.log("Game process started.");
	
	gameProcess.waitForFinished(-1);
	
	gameProcess.close();
	gameProcess = null;
});
launchEngine.text = "Launch Game";


//----------------------------------------------------
function removeAllLayers(CurTileMap){
	let mapLayerCount = CurTileMap.layerCount;
	for (let i = mapLayerCount; i > 0; i--){ 
		CurTileMap.removeLayerAt(i-1);
	}
}

function setLayerProperties(){
	layerStatic.setProperty('Collision',true);
	
	layerObjects.setProperty('Collision',true);
	layerObjects.setProperty('Interactable',true);
	
}


function addLayers(CurTileMap){
	CurTileMap.addLayer(layerBackground);
	CurTileMap.addLayer(layerDecoration);
	CurTileMap.addLayer(layerStatic);
	CurTileMap.addLayer(layerObjects);
	CurTileMap.addLayer(layerUI);
}


let buildWorld = tiled.registerAction("BuildWorld", function(action){
	openAsset = tiled.activeAsset;
	
	//is the currently open window a tileMap?
	if (openAsset.isTileMap){
		let confirmDialog = tiled.prompt('This process will delete all layers in this map, are you sure you want to continue?\nType confirm to continue','','Cancel');
		
		if (confirmDialog.toLowerCase() == 'confirm'){
			 
			 
			 setLayerProperties();
			 removeAllLayers(openAsset);
			 addLayers(openAsset);
			 tiled.alert("Process Complete.\nDo not alter layer names or custom properties.");
		 }else{
			 tiled.alert("Process Aborted"); 
			 return;
		 }
		
	}else{
		tiled.warn("openAsset is NOT a tileMap, make sure you have the map open for this process!!");
	}
});

buildWorld.text = "Initialise Scene";


//----------------------------------------------------
tiled.extendMenu("Map", [
	{action: "BuildWorld"}
]);

tiled.extendMenu("Map", [
	{action: "LaunchExecutable"}
]);




//----------------------------------------------------
//function graveyard


//let confirmDialog = ConfirmCancelDialogBox('This process deletes all layer data, are you sure you want to continue?\n','Yes');

// let confirmButton = null; 
// function ConfirmCancelDialogBox(heading,yesButtonText){
	// let dialogBox = new Dialog();
	// confirmButton = dialogBox.addButton(yesButtonText);
	
	
	// //let denyButton = dialogBox.addButton(noButtonText);
	// dialogBox.addHeading(heading);
	
 
	// dialogBox.show();
	
	// // while (dialogBox.finished !== true){
		// // if (confirmButton.checked){
			// // dialogBox.done(Dialog.Accepted);
		// // }
	// // }
	
	
	// //return dialogBox;
// }