package dominion;


class Cards {
  private String Name;
  private int cost;
  private int VictoryPoints; 
  private String Card_Type; 
  private Boolean EmbargoToken;

  public Cards(String name2, int coinCost, int vPoints, String type, Boolean EmbargoVal) {
	  	this.Name = name2;
	    this.cost = coinCost;
	    this.VictoryPoints = vPoints;
	    this.Card_Type = type;
	    this.EmbargoToken = EmbargoVal; 
}

  public String getName(){ return Name;}
  
  public Boolean getToken(){return EmbargoToken;}
  
 public int getCost(){return cost;}
 
  public String toString(){
    return Name+ " "+ cost + " " + VictoryPoints + " " + Card_Type + " " + EmbargoToken;
  }

  public void addEmbargo(){this.EmbargoToken = true;}
  
  
  public  String getType(){return Card_Type;}
  
}
