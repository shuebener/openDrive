
package uart;


import gnu.io.*; // RXTX
import java.util.Enumeration;
import java.util.ArrayList;
import java.util.concurrent.Semaphore;
import type.AvailablePorts_t;
import gui.*;


public class RS232 {
	
	public static ArrayList<AvailablePorts_t> Ports = new ArrayList<AvailablePorts_t>();
	public static Semaphore semaphore = new Semaphore(1, true);
	
	public static void updateAvailablePorts() {
		Enumeration AvailablePorts;
		CommPortIdentifier serialPortId;
		
		AvailablePorts = CommPortIdentifier.getPortIdentifiers();
		
		Ports.clear();
	    while (AvailablePorts.hasMoreElements()) {
	     	serialPortId = (CommPortIdentifier) AvailablePorts.nextElement();
	     	if(serialPortId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
				Ports.add(new AvailablePorts_t(serialPortId, serialPortId.getName()));
	    	}
	    }		
		
		return;
	}
	
	public static boolean Connect(String PortName) {
			
		int PortNr = RS232._getPortByName(PortName);
		if(PortNr == -1) {
			System.out.println("Port not found!");
			return(false);
		}
		
		if(Ports.get(PortNr).PortOpen) {
			return(true);
		}		
		
		try {
			Ports.get(PortNr).sp = (SerialPort) Ports.get(PortNr).PortID.open("Öffnen und Senden", 500);			
		} catch(Exception e) {
			System.out.println("Error: "+ e);
			return(false);
		}		
	
		try {
			Ports.get(PortNr).os = Ports.get(PortNr).sp.getOutputStream();
		} catch(Exception e) {
			System.out.println("Error: "+ e);
			return(false);
		}	
		

		try {
			Ports.get(PortNr).is = Ports.get(PortNr).sp.getInputStream();
		} catch (Exception e) {
			System.out.println("Error: "+ e);
			return(false);
		}
		
/*                
		try {
			SerialListener sl = new SerialListener();
			sl.setPortNr(PortNr);
			Ports.get(PortNr).sp.addEventListener(sl);
			Ports.get(PortNr).sp.notifyOnDataAvailable(true);
		} catch(Exception e) {
			System.out.println("Error: "+ e);
			return(false);
		}
*/	

		try {
			Ports.get(PortNr).sp.setSerialPortParams(Ports.get(PortNr).baudrate, Ports.get(PortNr).dataBits, Ports.get(PortNr).stopBits, Ports.get(PortNr).parity);
		} catch(Exception e) {
			System.out.println("Error: "+ e);
			return(false);
		}
		
		System.out.println("Connected to: "+ PortName);
		Ports.get(PortNr).PortOpen = true;
		
/*		
		System.out.println("test1");
		//while(!Ports.get(PortNr).test) {}
		try {
			Ports.get(PortNr).data_available.acquire();
		} catch(Exception e) {
			System.out.println("Error: "+ e);
		}
		System.out.println("test2");
*/
		
		return(true);
	}
	
	public static boolean CloseConnection(String PortName) {
		int PortNr = RS232._getPortByName(PortName);
		if(PortNr == -1) {
			System.out.println("Port not found!");
			return(false);
		}		
				
		try {
			Ports.get(PortNr).sp.close();
		} catch(Exception e) {
			System.out.println("Error: "+ e);
			return(false);
		}
		Ports.get(PortNr).PortOpen = false;
		System.out.println("Connection to "+ PortName +" closed...");
		
		return(true);
	}
	
	public static void startSenderTaskThread(String PortName, AVRFlasherGUI gui) {
		int PortNr = RS232._getPortByName(PortName);
		if(PortNr == -1) {
			System.out.println("Port not found!");
			return;
		}		
				
		if(Ports.get(PortNr).SenderTaskThread == null) {
			Ports.get(PortNr).SenderTaskThread = new SenderTask(PortNr, gui);			
		}				
	}
	
	public static void stopSenderTaskThread(int PortNr) {
		if(Ports.get(PortNr).SenderTaskThread != null) {
			Ports.get(PortNr).SenderTaskThread.stop();
			Ports.get(PortNr).SenderTaskThread = null;
		}		
	}
	
	public static void stopSenderTaskThread(String PortName) {
		int PortNr = RS232._getPortByName(PortName);
		if(PortNr == -1) {
			System.out.println("Port not found!");
			return;
		}			
		
		stopSenderTaskThread(PortNr);
	}	
	
	public static void setSettings(String PortName, int BaudRate, int DataBits, int StopBits, int Parity) {
		
		int PortNr = RS232._getPortByName(PortName);
		if(PortNr == -1) {
			System.out.println("Port not found!");
			return;
		}		
		
		Ports.get(PortNr).baudrate = BaudRate;
		Ports.get(PortNr).dataBits = DataBits;
		Ports.get(PortNr).stopBits = StopBits;
		Ports.get(PortNr).parity = Parity;			
		
		return;
	}
	
	public static boolean isConnected(String PortName) {
			
		int PortNr = RS232._getPortByName(PortName);
		if(PortNr == -1) {
			System.out.println("Port not found!");
			return(false);
		}
		
		if(Ports.get(PortNr).PortOpen) {
			return(true);
		} else {
			return(false);
		}
	}
	
	public static void SendString(int PortNr, String Message) {
		if(!Ports.get(PortNr).PortOpen) {
			System.out.println("Com-Port not open...");
		}
		try{
			Ports.get(PortNr).os.write(Message.getBytes());
			System.out.println("Send: "+ Message);
		} catch(Exception e) {
			System.out.println("Error: "+ e);
			return;			
		}		
	}
	
	public static void SendString(String PortName, String Message) {
		int PortNr = RS232._getPortByName(PortName);
		if(PortNr == -1) {
			System.out.println("Port not found!");
			return;
		}
		
		SendString(PortNr, Message);
	}
	
	public static void receiveData(int PortNr) {
		//DATA_AVAILABLE EventHandler...

		if(!Ports.get(PortNr).PortOpen) {return;}
		
		try {
			byte[] data = new byte[150];
			int num;
			while(Ports.get(PortNr).is.available() > 0) {
				num = Ports.get(PortNr).is.read(data, 0, data.length);
				System.out.println("Empfange: "+ new String(data, 0, num));
				Ports.get(PortNr).test = true;
			}
		} catch (Exception e) {
			System.out.println("Error: "+ e);
		}		
	}	
	
	public static String getReceivedData(String PortName) {
		return( getReceivedData(_getPortByName(PortName)) );
	}	
	
	public static String getReceivedData(int PortNr) {
		if(!Ports.get(PortNr).PortOpen) {return("");}
		String receive;
		try {
			byte[] data = new byte[150];
			int num;
			while(Ports.get(PortNr).is.available() > 0) {
				num = Ports.get(PortNr).is.read(data, 0, data.length);
				receive = new String(data, 0, num);
				//System.out.println("Empfange: "+ receive);
				Ports.get(PortNr).test = true;
				return(receive);
			}
		} catch (Exception e) {
			System.out.println("Error: "+ e);
			return("");
		}		
		
		return("");
	}
	
	protected static int _getPortByName(String PortName) {
		
		for( int i=0; i < Ports.size(); i++ ) {
			if(Ports.get(i).PortName.equals(PortName)) {
				return(i);
			}
		}
		
		return(-1);		
	}
		
}

class SerialListener implements SerialPortEventListener {
	
	public int PortNr;
	
	public void setPortNr(int sPortNr) {
		PortNr = sPortNr;
	}
	
	@Override
	public void serialEvent(SerialPortEvent event) {
		switch (event.getEventType()) {
			case SerialPortEvent.DATA_AVAILABLE:
				RS232.receiveData(PortNr);
				break;
			case SerialPortEvent.BI:
			case SerialPortEvent.CD:
			case SerialPortEvent.CTS:
			case SerialPortEvent.DSR:
			case SerialPortEvent.FE:
			case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
			case SerialPortEvent.PE:
			case SerialPortEvent.RI:
			default:
		}
	}
}
