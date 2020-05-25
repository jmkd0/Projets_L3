
public class GameEngine {
	private Parser parser;
    public Room currentRoom;
    private UserInterface gui;
    private Door door;
    private TransporterRoom transportRoom;
    private Room otherRooms[] = new Room[7];
    private int limitePlay;
    private Room beamerRoom = null;
    /**
     * Constructor for objects of class GameEngine
     */
    public GameEngine()
    {
        parser = new Parser();
        door   = new Door();
        
        createRooms();
        limitePlay = 0;
    }

    public void setGUI(UserInterface userInterface)
    {
        gui = userInterface;
        printWelcome();
    }

   

    /**
     * Create all the rooms and link their exits together.
     */
    private void createRooms()
    {
        Room piece1, piece2, piece3, piece4, piece5, piece6, piece7, transport;

        // create the rooms
        piece1 = new Room("Dongeon Cell", "dongeonCell.jpg");
        piece2 = new Room("Couslang Tour", "cell.jpg");
        piece3 = new Room("Ostagar", "piece4.jpg");
        piece4 = new Room("Royal room", "shot0025.jpg");
        piece5 = new Room("The Ishal Tower", "pont.jfif");
        piece6 = new Room("the computing admin office", "royal.jfif");
        piece7 = new Room("the computing admin office", "cell2.jpg");
        transport = new Room("Danger room", "transport.jpg");
        
        piece1.setExits("east", piece2);
        piece1.setExits("south", piece3);
        piece1.setExits("north", piece4);

        piece2.setExits("west", piece1);
        piece2.setExits("east", transport);

        piece3.setExits("north", piece1);
        piece3.setExits("west", piece6);

        piece4.setExits("south", piece1);
        piece4.setExits("north", piece7);
        piece4.setExits("west", piece5);

        piece5.setExits("east", piece4);

        piece6.setExits("east", piece3);

        piece7.setExits("south", piece4);
        
        transport.setExits("east", piece2);

        
        otherRooms[0] = piece1; otherRooms[1] = piece2; otherRooms[2] = piece3; 
        otherRooms[3] = piece4; otherRooms[4] = piece5; otherRooms[5] = piece6;
        otherRooms[6] = piece7;
        
        
        door.setLocked(piece4, piece5);
        door.setLocked(piece4, piece1);
        door.setLocked(piece4, piece7);
        

        this.currentRoom = piece1;
    }
/**
     * Print out the opening message for the player.
     */
    private void printWelcome()
    {
        gui.print("\n");
        gui.println("Welcome to the Hardes Game!");
        gui.println("Hardes is a new, incredibly boring adventure game.");
        gui.println("Type 'help' if you need help.");
        gui.print("\n");
        gui.println(this.currentRoom.getLongDescription());
        gui.showImage(currentRoom.getImageName());
    } 
    /**
     * Given a command, process (that is: execute) the command.
     * If this command ends the game, true is returned, otherwise false is
     * returned.
     */
    public void interpretCommand(String commandLine) {
        gui.println(commandLine);
        
        if(door.isDoorKey(commandLine)) {
        	door.setOpenDoor(commandLine);
        	return;
        }
        
        Command command = parser.getCommand(commandLine);
        if(command.isUnknown()) {
            gui.println("I don't know what you mean...");
            return;
        }

        String commandWord = command.getCommandWord();
        beamToRoom(commandWord);
        if (commandWord.equals("help"))
            printHelp();
        else if (commandWord.equals("go")) {
        	if(limitePlay < 10) { //Limit of playing: 10 times of holding goRome key
        		goRoom(command);
        		limitePlay++;
        	}else {
        		gui.println("You lose you have finish your possibilities the game");
        		endGame();
        	}
        }else if (commandWord.equals("quit")) {
            if(command.hasSecondWord())
                gui.println("Quit what?");
            else
                endGame();
        }
    }
    private void beamToRoom(String commandWord) {
    	if(commandWord.equals("charge")) {
        	beamerRoom = currentRoom;
        	gui.println("You have succefully charged the room"+currentRoom.getDescription());
        }else if(commandWord.equals("fire")) {
        	if(beamerRoom == null) gui.println("You have no room to beam");
        	else {
        		gui.println(beamerRoom.getLongDescription());
                if(beamerRoom.getImageName() != null)
                    gui.showImage(beamerRoom.getImageName());
        		gui.println("You have succefully fire inside "+beamerRoom.getDescription()+" room");
        	}
        	beamerRoom = null;
        }
    }

    // implementations of user commands:

    /**
     * Print out some help information.
     * Here we print some stupid, cryptic message and a list of the 
     * command words.
     */
    private void printHelp() 
    {
        gui.println("You are lost. You are alone. You wander");
        gui.println("around at Monash Uni, Peninsula Campus." + "\n");
        gui.print("Your command words are: " + parser.showCommands());
    }

    /** 
     * Try to go to one direction. If there is an exit, enter the new
     * room, otherwise print an error message.
     */
    private void goRoom(Command command) 
    {
        if(!command.hasSecondWord()) {
            // if there is no second word, we don't know where to go...
            gui.println("Go where?");
            return;
        }

        String direction = command.getSecondWord();

        // In Danger room the transporter kick him to other random room
        if(currentRoom.getDescription() == "Danger room") {
        	transportRoom = new TransporterRoom(gui, otherRooms);
        }
        else if(currentRoom.getDescription() == "Royal room" && direction == "west") {
        	gui.println("Attention you can't go back through the west side in Royal room");
        }
        else{
        	Room nextRoom = currentRoom.getExit(direction);
            if (nextRoom == null)
                gui.println("There is no door!");
            else {
            	String  key = door.checkLockedKey(currentRoom.getDescription(), nextRoom.getDescription());
            	
            	if(key != null) {
            		//currentRoom = nextRoom;
            		gui.println("This door is looked, You have to unlock it by key");
            		gui.println("Choose a key bellow to unlock this door");
            		door.openDoorWithKey(gui, currentRoom, key, direction);
            	}
            	else {
            		currentRoom = nextRoom;
                    gui.println(currentRoom.getLongDescription());
                    if(currentRoom.getImageName() != null)
                       gui.showImage(currentRoom.getImageName());
            	}
            	
               
            }
        }
        
    }

    private void endGame(){
        gui.println("Thank you for playing.  Good bye.");
        gui.enable(false);
    }

    public Parser getParser() {
        return parser;
    }
}
