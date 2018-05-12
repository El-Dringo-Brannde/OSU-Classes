//
//  NumberTableViewCell.swift
//  CS 496 - HW 4
//
//  Created by Dring, Brandon on 2/16/18.
//  Copyright © 2018 Dring, Brandon. All rights reserved.
//

import UIKit

class NumberTableViewCell: UITableViewCell {
    // MARK: Properties

    @IBOutlet weak var NumberLabel: UILabel!
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
