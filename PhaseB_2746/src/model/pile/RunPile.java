/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model.pile;

import javax.swing.JOptionPane;
import model.player.Player;
import model.card.Card;
import model.card.HazardCardEnumType;
import model.card.RemedyCardEnumType;
import model.card.SafetyCardEnumType;

/**
 *
 * @author Kostas Goumas
 */
public class RunPile {

    Card card;


    public Card getLastCard() {
        return card;
    }

    public void setCard(Card crd) {
        this.card = crd;

    }

    public void removeCard() {
        this.card = null;
    }

    public boolean addToRunPile(Player p, Card c ) {
        if (p.getSafetyPile().containsCard(SafetyCardEnumType.RIGHT_OF_WAY)) {
            JOptionPane.showMessageDialog (null, "Right of Way card exists", "Error", JOptionPane.INFORMATION_MESSAGE);
            
			return false;
        } else if (getLastCard()!=null && getLastCard().toString().equals(HazardCardEnumType.SPEED_LIMIT.toString()) && c.toString().equals(RemedyCardEnumType.END_OF_LIMIT.toString())) {
            this.card = c;
            return true;
        }
            JOptionPane.showMessageDialog (null, "Cannot Play this Card into Run Stack", "Error", JOptionPane.INFORMATION_MESSAGE);

        return false;
    
    }
    public boolean opponentAddToRunPile(Player p, Card c ) {
        if (p.getSafetyPile().containsCard(SafetyCardEnumType.RIGHT_OF_WAY)) {
            JOptionPane.showMessageDialog (null, "Right of Way card exists", "Error", JOptionPane.INFORMATION_MESSAGE);
			
            return false;
        } else if (c.toString().equals(HazardCardEnumType.SPEED_LIMIT.toString()) && (this.getLastCard()==null || !this.getLastCard().toString().equals(HazardCardEnumType.SPEED_LIMIT.toString()))) {
            this.card = c;
            return true;
        }
        JOptionPane.showMessageDialog (null, "Cannot Play this Card into Run Stack", "Error", JOptionPane.INFORMATION_MESSAGE);

        return false;
    
    }
}
