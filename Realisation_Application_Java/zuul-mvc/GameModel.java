import java.util.Observable;

/**
 * GameModel represents the model of the game. This 
 * 
 * @author Poul Henriksen
 * @version  1.0 (February 2005)
 */
public class GameModel extends Observable
{
    private Room currentRoom;
    
    public GameModel()
    {
        createRooms();
    }

    /**
     * Create all the rooms and link their exits together.
     */
    private void createRooms()
    {
        Room outside, theatre, pub, lab, office;

        // create the rooms
        outside = new Room("outside the main entrance of the university");
        theatre = new Room("in a lecture theatre");
        pub = new Room("in the campus pub");
        lab = new Room("in a computing lab");
        office = new Room("in the computing admin office");

        // initialise room exits
        outside.setExits(null, theatre, lab, pub);
        theatre.setExits(null, null, null, outside);
        pub.setExits(null, outside, null, null);
        lab.setExits(outside, office, null, null);
        office.setExits(null, null, null, lab);

        currentRoom = outside; // start game outside
    }

    public Room getCurrentRoom()
    {
        return currentRoom;
    }

    public void goRoom(Room nextRoom)
    {
        currentRoom = nextRoom;
        setChanged();
        notifyObservers();
    }
    
    public String getWelcomeString() 
    {
        return "Welcome to the World of Zuul!" + "\n" + 
               "World of Zuul is a new, incredibly boring adventure game.";
    }
    
    public String getGoodByeString()
    {
        return "Thank you for playing.  Good bye.";
    }
    
    public String getHelpString()
    {
        return "You are lost. You are alone. You wander" + "\n" +
                "around at the university.";
    }
    
    public String getLocationInfo() {
        return "You are " + getCurrentRoom().getDescription() + "\n" +
                getCurrentRoom().getExitString();
    }
}