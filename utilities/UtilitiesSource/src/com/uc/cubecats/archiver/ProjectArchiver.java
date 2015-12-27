package com.uc.cubecats.archiver;

import java.io.File;
import java.io.IOException;

public class ProjectArchiver {
	
	// Variables
	private static boolean isArchiving;
	private static String inputPath;
	private static String outputPath;
	private static String filename;
	private static String[] excludes;
	
	/**
	 * This function serves as the entry point into the utility to begin
	 * the file copying process.  Currently, command-line arguments are
	 * not supported.
	 * 
	 * @param args Command-line arguments, which are not supported currently.
	 */
	public static void main(String[] args) {
		
		/* Parse the terminal arguments to determine the actions to be carried out. */
		boolean argsPassed = parseArguments(args);
		
		/* Print out an error message and exit if the argument parsing failed. */
		if(!argsPassed) {
			// TODO - error...
			System.exit(1);
		}
		
		/* Carry-out the appropriate action desired by the user. */
		if(isArchiving) {
			archiveFiles();
		} else {
			extractArchive();
		}
		
	}
	
	private static void setupDefaults() {
		isArchiving = true;
		inputPath = "..";
		outputPath = "../archive";
		filename = "archive.exx";
		excludes = null;
	}
	
	private static boolean parseArguments(String[] args) {
		
		/* Create a flag to determine if the arguments supplied are sufficient. */
		boolean argsPassed = false;
		
		/* Create a flag specifically for verifying the mode was set properly. */
		boolean modeIsValid = false;
		
		/* Setup any default values for arguments. */
		setupDefaults();
		
		/* Go through each argument to extract the info. */
		for(int i = 0; i < args.length; i++) {
			
			/* Case for the "inputDir" argument. */
			if(args[i].startsWith("-inputDir=")) {
				inputPath = args[i].substring(10, args[i].length());
			}
			
			/* Case for the "outputDir" argument. */
			if(args[i].startsWith("-outputDir=")) {
				outputPath = args[i].substring(11, args[i].length());
			}
			
			/* Case for the "mode" argument. */
			if(args[i].startsWith("-mode=")) {
				String modeTmp = args[i].substring(6, args[i].length());
				if(modeTmp.equalsIgnoreCase("archive")) {
					isArchiving = true;
					modeIsValid = true;
				} else if(modeTmp.equalsIgnoreCase("extract")) {
					isArchiving = false;
					modeIsValid = true;
				}
			}
			
			/* Case for the "mode" argument. */
			if(args[i].startsWith("-filename=")) {
				filename = args[i].substring(10, args[i].length());
				if(!filename.toLowerCase().endsWith(".exx")) {
					filename += ".exx";
				}
			}
			
			/* Case for the "exclude" argument. */
			if(args[i].startsWith("-exclude=")) {
				excludes = args[i].substring(11, args[i].length()).split(",");
			}
		}
		
		/* Determine if the arguments were properly parsed. */
		argsPassed = modeIsValid && (inputPath != null) && (outputPath != null) && (filename != null);
		
		/* Return the results of the argument parsing. */
		return argsPassed;
	}

	private static void archiveFiles() {
		
		/* Get a reference to the input path. */
		File copyDir = new File(inputPath);
		
		/* Verify that the build path exists before proceeding. */
		if(!(copyDir.exists() && copyDir.isDirectory())) {
			return;
		}
		
		/* If the archive path doesn't exist, create it. */
		File archiveDir = new File(outputPath);
		if(!archiveDir.exists()) {
			archiveDir.mkdir();
		}
		
		/* Setup the archive manager and add the exclusion patterns if applicable. */
		ArchiveManager archiveManager = new ArchiveManager();
		if(excludes != null) {
			archiveManager.addExcludes(excludes);
		}
		
		/* Create the archive. */
		try {
			archiveManager.archiveFile(copyDir, new File(outputPath + File.separator + filename), true);
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	private static void extractArchive() {
		ArchiveManager archiveManager = new ArchiveManager();
		try {
			archiveManager.extractArchive(new File(inputPath + File.separator + filename), new File(outputPath), true, true);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
}