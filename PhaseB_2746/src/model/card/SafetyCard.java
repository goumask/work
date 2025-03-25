/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model.card;

import model.card.Card;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 * @author Kostas Goumas
 */
public class SafetyCard implements Card {

	private int value;
	private int points;
	SafetyCardEnumType safetyCardEnum;

	public SafetyCard(SafetyCardEnumType sEnum) {
		safetyCardEnum = sEnum;
	}
        public SafetyCardEnumType getSafetyCardEnum(){
            return safetyCardEnum;
        }

	@Override
	public int getValue() {
		return value;
	}

	@Override
	public void setValue(int value) {
		this.value = value;
	}

	@Override
	public int getPoints() {
		return points;
	}

	@Override
	public void setPoints(int points) {
		this.points = points;
	}
	
	@Override
	public String toString(){
		return safetyCardEnum.toString();
	}
        
        public String getType(){
            return "Safety";
        }
}
