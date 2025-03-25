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
public class MilesCard implements Card {

	private int value;

    public int getMiles() {
        return miles;
    }
	private int points,miles;

	public MilesCard(int miles) {
		this.miles=miles;
	}

        public String getType(){
            return "Miles";
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
		return "Miles_"+miles;
	};

        //oi methodoi den kanoun kati sigekrimeno prepei na ginoun implement afou einai sto interface
    @Override
    public int getValue() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void setValue(int value) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}
