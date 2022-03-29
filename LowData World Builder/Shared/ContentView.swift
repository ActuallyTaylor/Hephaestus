//
//  ContentView.swift
//  Shared
//
//  Created by Zachary lineman on 3/25/22.
//

import SwiftUI
import UniformTypeIdentifiers

struct ContentView: View {
    @StateObject var handler: ContentHandler = ContentHandler()
    @State var selectWorldPopup: Bool = false
    
    var body: some View {
        HStack {
            // World data view
            VStack {
                Text("Low Data World Builder")
                    .font(.title)
                    .padding()
                
                VStack(alignment: .leading) {
                    // Enter the name of the world
                    Text("Name")
                        .foregroundColor(.secondary)
                    TextField("World Name", text: $handler.worldName)
                    
                    // Enter the description of the world
                    Text("Description")
                        .foregroundColor(.secondary)
                    TextEditor(text: $handler.worldDescription)
                        .frame(height: 64)
                    
                    Text("World Size")
                        .foregroundColor(.secondary)
//                    TextField("World Width", value: $handler.mapWidth, formatter: NumberFormatter())
//                    TextField("World Height", value: $handler.mapHeight, formatter: NumberFormatter())
                    
                    Text("Layer Details")
                    TextField("Layer Name", text: $handler.layerName)
                    TextEditor(text: $handler.layerDescription)
                        .frame(height: 64)
                }
                .padding()
                HStack {
                    Button {
                        handler.exportWorld()
                    } label: {
                        Text("Export World")
                    }
                    Button {
                        handler.saveWorld()
                    } label: {
                        Text("Save World")
                    }
                    Button {
                        selectWorldPopup.toggle()
                    } label: {
                        Text("Load World")
                    }
                    .popover(isPresented: $selectWorldPopup) {
                        WorldLoader(showSheet: $selectWorldPopup)
                            .environmentObject(handler)
                    }

                }
                Spacer()
            }
            .frame(width: 300)
            Divider()
            VStack {
                Text("World")
                    .font(.title)
                    .padding()
                ZStack {
                    Map(layer: handler.currentLayer)
                        .environmentObject(handler)
                }
            }
            .frame(width: 600)
            Divider()
            VStack {
                VStack {
                    Text("Tiles")
                        .font(.title)
                    ScrollView([.horizontal]) {
                        HStack {
                            ForEach(handler.images, id: \.self) { image in
                                Image(image)
                                    .border(handler.images[handler.selectedTileIndex] == image ? Color.accentColor : Color.black, width: 1)
                                    .onTapGesture {
                                        handler.selectedTileIndex = handler.images.firstIndex(of: image) ?? 0
                                    }
                            }
                        }
                    }
                }
                .padding()
                Divider()
                VStack {
                    Text("Layers")
                        .font(.title)
                    ScrollView([.vertical]) {
                        VStack {//(columns: threeColumnGrid) {
                            ForEach(handler.layers, id: \.id) { layer in
                                HStack {
                                    Text(layer.name)
                                        .padding(5)
                                    Spacer()
                                }
                                .background(handler.currentLayer == layer ? Color.accentColor : Color.clear)
                                .cornerRadius(7)
                                .onTapGesture {
                                    handler.selectLayer(index: handler.layers.firstIndex(of: layer) ?? 0)
                                }
                            }
                            HStack {
                                Image(systemName: "plus")
                                    .resizable()
                                    .frame(width: 32, height: 32)
                                
                                Text("Add Layer")
                                Spacer()
                            }
                            .frame(width: 250, height: 44)
                            .onTapGesture {
                                handler.createNewLayer()
                            }
                        }
                    }
                }
                .padding()
                Spacer()
            }
            .frame(width: 300)
        }
        .fileExporter(isPresented: $handler.fileExporterOpen, document: handler.exportFile, contentType: .lDataWorld, onCompletion: {  result in
            switch result {
            case .success(let url):
                print("Saved to \(url)")
            case .failure(let error):
                print(error.localizedDescription)
            }
        })
    }
}

struct WorldLoader: View {
    @Binding var showSheet: Bool
    @EnvironmentObject var handler: ContentHandler

    var body: some View {
        ScrollView([.vertical]) {
            VStack {//(columns: threeColumnGrid) {
                ForEach(handler.worlds) { world in
                    HStack {
                        Text(world.name)
                            .padding(5)
                        Spacer()
                    }
                    .background(Color(nsColor: NSColor.systemGray))
                    .cornerRadius(5)
                    .padding(3)
                    .onTapGesture {
                        self.showSheet = false
                        handler.loadWorld(world: world)
                    }
                    .contextMenu {
                      Button(action:{
                          handler.worlds.removeAll { nWorld in
                              return world.id == nWorld.id
                          }
                          handler.saveAllWorlds()
                      }){
                        Text("Delete")
                      }
                    }
                }
                HStack {
                    Image(systemName: "plus")
                        .resizable()
                        .frame(width: 32, height: 32)
                    
                    Text("Add World")
                    Spacer()
                }
                .frame(width: 250, height: 44)
                .onTapGesture {
                    handler.saveWorld()
                    handler.clearCurrentWorld()
                }
            }
        }
    }
}

struct Map: View {
    
    @EnvironmentObject var handler: ContentHandler
    var layer: ContentHandler.Layer
    
    var body: some View {
        ScrollView ([.horizontal, .vertical], showsIndicators: true) {
            VStack(spacing: 0) {
                ForEach(0..<$handler.mapHeight.wrappedValue, id: \.self) { y in
                    let y = handler.mapWidth - 1 - y
                    HStack(spacing: 0) {
                        ForEach(0..<$handler.mapWidth.wrappedValue, id: \.self) { x in
                            VStack {
                                Image(nsImage: NSImage(named: handler.images[handler.currentLayer.layerMatrix[x, y]])!)
                                    .resizable()
                                    .frame(width: 16, height: 16)
                                    .border(layer.layerMatrix[x,y] == 0 ? Color.black : Color.clear, width: 1)
                            }
                            .border((($handler.selectedTileX.wrappedValue == x && $handler.selectedTileY.wrappedValue == y) ? Color.accentColor : Color.clear), width: 1)
                            .frame(width: 16, height: 16)
                            .onTapGesture(perform: {
                                handler.selectedTileX = x
                                handler.selectedTileY = y
                                if layer.layerMatrix[x, y] != handler.selectedTileIndex {
                                    layer.layerMatrix[x, y] = handler.selectedTileIndex
                                } else {
                                    layer.layerMatrix[x, y] = 0
                                }
//                                screenshotWorld()
                            })
                        }
                    }
                }
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
