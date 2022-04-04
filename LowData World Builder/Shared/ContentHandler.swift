//
//  ContentHandler.swift
//  LowData World Builder
//
//  Created by Zachary lineman on 3/26/22.
//

import Foundation
import AppKit

class ContentHandler: ObservableObject  {
    
    @Published var worlds: [World] = []
    
    @Published var fileExporterOpen: Bool = false
    @Published var exportFile: TextFile = TextFile(initialText: "")
    
    @Published var mapWidth: Int = 32

    @Published var mapHeight: Int = 32
    @Published var worldName: String = ""
    @Published var worldDescription: String = ""
    var worldUUID: UUID = UUID()
    
    @Published var layerName: String = ""
    @Published var layerDescription: String = ""

    var images: [String] = ["Empty", "Grass", "Dirt", "Stone", "Wood", "Water", "Fence_Full", "Fence_Left_Half", "Fence_Right_Half", "Fence_Poll"]
    var collisionImages: [String] = ["Fence_Full", "Fence_Left_Half", "Fence_Right_Half", "Fence_Poll"]

    class World: Codable, Identifiable {
        var name: String
        var description: String
        var id: UUID
        var layers: [Layer]
        
        init(name: String, description: String, id: UUID, layers: [ContentHandler.Layer]) {
            self.name = name
            self.description = description
            self.id = id
            self.layers = layers
        }
    }
    
    class Layer: Equatable, Codable, Identifiable, Hashable {
        init(name: String, id: UUID = UUID(), description: String, layerMatrix: Matrix) {
            self.name = name
            self.description = description
            self.id = id
            self.layerMatrix = layerMatrix
//            self.layerImage = layerImage
        }
        
        static func == (lhs: ContentHandler.Layer, rhs: ContentHandler.Layer) -> Bool {
            return lhs.id == rhs.id
        }
        
        var name: String
        var description: String
        var id: UUID = UUID()
        var layerMatrix: Matrix
        
        func hash(into hasher: inout Hasher) {
            hasher.combine(id)
        }
    }
    
    @Published var layers: [Layer] = []
    @Published var currentLayer: Layer!
    @Published var layerOpacity: CGFloat = 0.5
    
    @Published var selectedTileX: Int = 0
    @Published var selectedTileY: Int = 0
    @Published var selectedTileIndex: Int = 0
    
    public init() {
        layers.append(Layer(name: "Background", description: "A background layer", layerMatrix: Matrix(rows: mapWidth, columns: mapHeight)))
        selectLayer(index: 0)
        
        worlds = getWorlds()
    }
    
    func createNewLayer() {
        layers.append(Layer(name: "New Layer", description: "A new layer", layerMatrix: Matrix(rows: mapWidth, columns: mapHeight)))
    }
    
    func selectLayer(index: Int) {
        currentLayer = layers[index]
        layerName = currentLayer.name
        layerDescription = currentLayer.description
    }
    
    func getWorlds() -> [World] {
        var worlds: [World] = []
        if UserDefaults.standard.object(forKey: "Worlds") != nil {
            let storedObject: Data = UserDefaults.standard.object(forKey: "Worlds") as? Data ?? Data()
            let storedList: [World] = try! PropertyListDecoder().decode([World].self, from: storedObject)
            
            worlds.append(contentsOf: storedList)
        }
        return worlds
    }
    
    func loadWorld(world: World) {
        layers = world.layers
        currentLayer = layers[0]
        worldDescription = world.description
        worldName = world.name
        worldUUID = world.id
    }
    
    func saveAllWorlds() {
        UserDefaults.standard.set(try? PropertyListEncoder().encode(worlds), forKey: "Worlds")
    }
    
    func saveWorld() {
        var worlds: [World] = []
        if UserDefaults.standard.object(forKey: "Worlds") != nil {
            let storedObject: Data = UserDefaults.standard.object(forKey: "Worlds") as? Data ?? Data()
            let storedList: [World] = try! PropertyListDecoder().decode([World].self, from: storedObject)
            
            worlds.append(contentsOf: storedList)
        }
        
        let world = World(name: worldName, description: worldDescription, id: worldUUID, layers: layers)
        
        if worldName != "" {
            worlds.removeAll { listWorld in
                return listWorld.id == worldUUID
            }
            worlds.append(world)
            UserDefaults.standard.set(try? PropertyListEncoder().encode(worlds), forKey: "Worlds")
            
            self.worlds = worlds
        }
    }
    
    func clearCurrentWorld() {
        layers = [Layer(name: "Background", description: "A background layer", layerMatrix: Matrix(rows: mapWidth, columns: mapHeight))]
        worldDescription = ""
        worldName = ""
        worldUUID = UUID()
    }
    
    func exportWorld() {
        var layerContents: String = ""
        
        //NAME, X, Y, Z, WIDTH, HEIGHT, RotX, RotY, RotZ
        var dataContents: String = ""
        let tileSize = 32
        for layer in layers {
            layerContents.append("  - \(layerName): \(layerDescription)\n")
            for x in 0 ..< mapHeight {
                for y in 0 ..< mapHeight {
                    let value = layer.layerMatrix[x, y]
                    let name = images[value]
                    if name.lowercased() != "empty" {
                        let xPosition = 32 * x
                        let yPosition = 32 * y
                        let isCollision = collisionImages.contains(name)
                        
                        let line = "\(name), \(xPosition), \(yPosition), 0, \(tileSize), \(tileSize), 0, 0, 0, \(isCollision ? "1" : "0")\n"
                        dataContents.append(line)
                    }
                }
            }
        }
        
        let finalFileContents: String = """
        FORMAT: ITEM_NAME,StartX,StartY,StartZ,WIDTH,HEIGHT,RotX,RotY,RotZ,CollisionEntity
        WORLD NAME: \(worldName)
        WORLD DESCRIPTION: \(worldDescription)
        
        LAYERS:
        \(layerContents)
        
        === ALL DATA ABOVE THIS LINE WILL BE IGNORED ===
        \(dataContents)
        """

        exportFile = TextFile(initialText: finalFileContents)
        fileExporterOpen.toggle()

    }
}
