GECCCOS HMI

Current Release: V1.0

Changelog:
	* Initial Release
	* V1 of the thesis attached
	* V1 of the test procedure book attached
	
Previous Releases:




Introduction:
GECCCOS HMI is a simple program to ease up the configuration of calculations using GECCCOS. 
The HMI itself is completely decoupled from GECCCOS. It is only used to generate and manipulate input values for calculations. 


Installation:
WINDOWS: Unzip the latest zip file from the executeables directory and open the GECCCOS_HMI.exe file
Other platforms are not supported yet. Let me know, if you need a linux or mac distribution. 

Use:
To open a GECCCOS project with the HMI you need to provide a hmi_config.json file to specify the files of the project. This hmi_config.json file has to be in the same directory as the input, output and work directories. 
Once the HMI is opened, you can select any directory as GECCCOS project and the HMI will load the according config to interpret the files contained in the GECCCOS project. 
example a project in the folder named O16:
	*O16
		- work
		- input
		- output
		- hmi_config.json
To open this kine of project, navigate to the O16 folder and open it


HELP, Something is not working:
Please send me an email to e0846328@student.tuwien.ac.at with the following information:
* What did you do before the error happened
* What's the expected behaviour
* What's the experienced behaviour
* The project you were using (including the config)
For an example for such a software test, see the excel table in the tests directory. 

Further documentation:
Further documentation can be found in my project thesis, located in the thesis directory. (Unfortunately, the theses is only available in german)
