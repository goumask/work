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
public class RemedyCard implements Card {

	private int value;
	private int points;
	RemedyCardEnumType remedyCardEnum;

	public RemedyCard(RemedyCardEnumType sEnum) {
		remedyCardEnum = sEnum;
	}

         public RemedyCardEnumType getRemedyCardEnum(){
            return remedyCardEnum;
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
	public String getType(){
            return "Remedy";
        }
	@Override
	public String toString(){
		return remedyCardEnum.toString();
	}
}
