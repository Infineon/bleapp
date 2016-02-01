//
//  RcCar.swift
//  BleRemote
//


class RcCar {
    var connection : BleConnection
    
    init (connection : BleConnection)
    {
        self.connection = connection
        connection.car = self
    }
    
    var speedLeft : Int8 = 0 {
        didSet {
            connection.writeLeftSpeed(speedLeft)
        }
    }
 
    var speedRight : Int8 = 0 {
        didSet {
            connection.writeRightSpeed(speedRight)
        }
    }
    
    var tachLeft = 0
    var tachRight = 0
}
