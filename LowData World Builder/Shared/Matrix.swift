//
//  Matrix.swift
//  LowData World Builder
//
//  Created by Zachary lineman on 3/26/22.
//

import Foundation

//Inspired by https://medium.com/@michael.m/creating-a-matrix-class-in-swift-3-0-a7ae4fee23e1
public class Matrix: CustomStringConvertible {
    internal var data: Array<Int>
    
    public var rows: Int
    public var columns: Int
    
    public subscript(row: Int, col: Int) -> Int {
        get {
            return data[(row * columns) + col]
        }
        set(newValue) {
            self.data[(row * columns) + col] = newValue
        }
    }
    
    public init(_ data:Array<Int>, rows:Int, columns:Int) {
        self.data = data
        self.rows = rows
        self.columns = columns
    }
    
    public init(rows:Int, columns:Int) {
        self.data = [Int](repeating: 0, count: rows*columns)
        self.rows = rows
        self.columns = columns
    }
    
    public var description: String {
        var desc = ""
        for col in 0..<columns {
            for row in 0..<rows {
                let string = "\(self[row, col])"
                desc += string + ""
            }
            desc += "\n"
        }
        
        return desc
    }
    
    required public init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: Key.self)
        rows = try container.decode(Int.self, forKey: .rows)
        columns = try container.decode(Int.self, forKey: .columns)
        data = try container.decode(Array<Int>.self, forKey: .data)
    }
}

extension Matrix: Codable {
    enum Key: CodingKey {
        case columns
        case rows
        case data
    }
    
    public func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: Key.self)
        try container.encode(rows, forKey: .rows)
        try container.encode(columns, forKey: .columns)
        try container.encode(data, forKey: .data)
    }

}

