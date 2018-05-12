//
//  DataTableViewCell.swift
//  CS 496 - HW 5
//
//  Created by Dring, Brandon on 2/23/18.
//  Copyright © 2018 Dring, Brandon. All rights reserved.
//

import UIKit

class DataTableViewCell: UITableViewCell {
    
    @IBOutlet weak var Data: UILabel!
    @IBOutlet weak var Lat: UILabel!
    @IBOutlet weak var Lng: UILabel!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)
        // Configure the view for the selected state
    }

}
