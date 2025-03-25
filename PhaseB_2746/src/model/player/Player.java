/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model.player;

import java.util.HashMap;
import model.card.Card;
import model.pile.BattlePile;
import model.pile.RunPile;
import model.pile.MilesPileProcess;
import model.pile.SafetyPile;

/**
 * @author Kostas Goumas
 */
public class Player {

    private String name;
    private HashMap<Integer, Card> cards;
    private String[] images;
    private int choice, ID;
    private BattlePile battlepile;
    private MilesPileProcess milespile;
    private SafetyPile safetypile;
    private RunPile runpile;
    private int miles;
    private boolean hasPlayed, finished;
    private boolean Turn;
    private boolean Winner;

    public Player(String name, int ID) {

        this.name = name;

        choice = 0;
        hasPlayed = false;
        battlepile=new BattlePile();
        milespile=new MilesPileProcess();
        safetypile=new SafetyPile();
        runpile=new RunPile();
        this.ID = ID;
        finished = false;
    }

    public BattlePile getBattlePile() {
        return battlepile;
    }

    public MilesPileProcess getMilesPile() {
        return milespile;
    }

    public SafetyPile getSafetyPile() {
        return safetypile;
    }

    public RunPile getRunPile() {
        return runpile;
    }

    public HashMap<Integer, Card> getPlayerCards() {
        return cards;
    }

    public void setPlayerCards(HashMap<Integer, Card> cards) {
        this.cards = cards;
    }


    public void init_player() {

        this.choice = 0;
        this.hasPlayed = false;

        this.finished = false;
    }

    public int getID() {
        return ID;
    }

    public void setID(int id) {
        this.ID = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String newName) {
        this.name = newName;
    }

    public void hasPlayed() {
        this.hasPlayed = true;
    }

    public void has_finished() {
        this.finished = true;
    }

    public boolean isTurn() {
        return Turn;
    }

    public void setTurn(boolean turn) {
        Turn = turn;
    }


    public boolean Has_Played() {
        return this.hasPlayed;
    }

    public boolean Get_has_finished() {
        return this.finished;
    }

    public void setIsWinner(boolean winner) {
        this.Winner=winner;
    }

    public boolean isWinner() {
        return this.Winner;
    }
}
