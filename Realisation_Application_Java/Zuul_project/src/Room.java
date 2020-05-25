import java.util.HashMap;
import java.util.Set;

public class Room {
	private HashMap<String, Room> exits;
	private String description;
	private String imageName;
	
    /**
     * Create a room described "description". Initially, it has
     * no exits. "description" is something like "a kitchen" or
     * "an open court yard".
     * @param description The room's description.
     */
    public Room(String description, String image) 
    {
        this.description = description;
        exits = new HashMap<String, Room>();
        imageName = image;
        
        //this.exits.put(direction, neighbor);
    }

    

	/**
     * Define the exits of this room.  Every direction either leads
     * to another room or is null (no exit there).
     * @param north The north exit.
     * @param east The east east.
     * @param south The south exit.
     * @param west The west exit.
     */
    /*public void setExits(Room north, Room east, Room south, Room west) 
    {
        if(north != null)
            northExit = north;
        if(east != null)
            eastExit = east;
        if(south != null)
            southExit = south;
        if(west != null)
            westExit = west;
    }*/
    public void setExits(String direction, Room neighbor)
    {
        exits.put(direction, neighbor);
    }
    
    public Room getExit(String direction) {
        return this.exits.get(direction);
    }

    /**
     * @return The description of the room.
     */
    public String getDescription()
    {
        return description;
    }
    
    public String getLongDescription(){
        return "Welcome to "+this.description + ".\n" + this.getExitString();
    }
    
    public String getExitString(){
        String returnString = "";
        Set<String> keys = this.exits.keySet();
        for (String exit : keys)
            returnString += " " + exit;
        return returnString;
    }
    
    public String getImageName()
	{
		return imageName;
	}
}
