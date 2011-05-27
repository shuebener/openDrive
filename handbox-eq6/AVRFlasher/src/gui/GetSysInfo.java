

package gui;

public class GetSysInfo {
	
	AVRFlasherGUI guih = null;
	
	public void setguih(AVRFlasherGUI gui) {
		this.guih = gui;
		return;
	}
	
	public void load() {
		String PortName = this.guih.getSelectedPortName();
		Thread gsit = new Thread(new GetSysInfo_Thread(this.guih, PortName), "GetSysInfo_Thread");
		gsit.start();
						
		return;
	}
	
	

}
