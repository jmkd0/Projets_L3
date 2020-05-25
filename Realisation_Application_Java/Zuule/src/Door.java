import java.util.HashMap;
import java.util.Random;
import java.util.Iterator;
import java.util.Set;

public class Door {
	private HashMap<String, HashMap<String, String>> lockedDoors;
	private UserInterface gui;
	private Room currentRoom;
	private Room nextRoom;
	private String key; 
	private String keys[] = {getKey(),getKey(),getKey(),getKey()};
	private String direction;
	
	public Door() {
		lockedDoors = new HashMap<String, HashMap<String, String>>();
		
	}
	public void setLocked(Room room1, Room room2) {
		HashMap<String, String> door = new HashMap<String, String>();
		door.put(room1.getDescription(), room2.getDescription());
		this.lockedDoors.put(this.getKey(), door);
	}
	//Check whether a door between two room is locked
	public String checkLockedKey(String desc1, String desc2) {
		String key = null;
		HashMap<String, String> door1 = new HashMap<String, String>();
		HashMap<String, String> door2 = new HashMap<String, String>();
		door1.put(desc2, desc1);
		door2.put(desc1, desc2);
		Set cles = lockedDoors.keySet();
		Iterator iterat = cles.iterator();
		while(iterat.hasNext()) {
			Object cle = iterat.next();
			Object ma = lockedDoors.get(cle);
			
			HashMap<String, String> map = (HashMap)ma;
			Set val1 = map.keySet();
			Iterator it = val1.iterator();
			Object room1 = it.next();
			Object room2 = map.get(room1);
			if(desc1 == (String)room1 && desc2 == (String)room2 || desc1 == (String)room2 && desc2 == (String)room1) {
				key = (String)cle;
				return key;
			}
		}
		return key;
	}
	//Init unlock infos
	public void openDoorWithKey(UserInterface gui, Room currentRoom, String key, String direction) {
		Random rand = new Random();
		int randKey = rand.nextInt(4);
		keys[randKey] = key;
		gui.println("---"+keys[0]+"---"+keys[1]+"---"+keys[2]+"---"+keys[3]+"---");
		this.gui = gui;
		this.key = key;
		this.currentRoom = currentRoom;
		this.direction = direction;
		
	}
	//Open locked door
	public void setOpenDoor(String input) {
		keys[0] = getKey(); keys[1] = getKey(); keys[2] = getKey(); keys[3] = getKey();
		Random rand = new Random();
		int randKey = rand.nextInt(4);
		keys[randKey] = key;
		gui.println("---"+keys[0]+"---"+keys[1]+"---"+keys[2]+"---"+keys[3]+"---");
		int intKey = Integer.parseInt(key);
		int intInput = Integer.parseInt(input);
		if(intKey == intInput ) {
			Room nextRoom = gui.engine.currentRoom.getExit(direction);
			gui.engine.currentRoom = nextRoom;
			gui.println("The door is opened succefully");
			gui.println(gui.engine.currentRoom.getLongDescription());
	        if(currentRoom.getImageName() != null)
	           gui.showImage(gui.engine.currentRoom.getImageName());
			
		}else {
			gui.println("You have entered a bad key, retry");
		}
	}
	
	//Check whether a command is a key
	public boolean isDoorKey(String str){
	    for (char c : str.toCharArray()){
	        if (!Character.isDigit(c)) return false;
	    }
	    return true;
	}
//get random key [100, 999]
	private String getKey() {
		Random rand = new Random();
		int value = rand.nextInt(999-100)+100;
		return String.valueOf(value);
	}
}
