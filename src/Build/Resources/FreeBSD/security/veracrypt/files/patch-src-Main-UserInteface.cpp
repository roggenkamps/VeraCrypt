--- src/Main/UserInterface.cpp.orig
+++ src/Main/UserInterface.cpp
@@ -838,12 +838,12 @@ namespace VeraCrypt
 #else
 		// MIME handler for directory seems to be unavailable through wxWidgets
 		wxString desktop = GetTraits()->GetDesktopEnvironment();
-		bool xdgOpenPresent = wxFileName::IsFileExecutable (wxT("/usr/bin/xdg-open"));
-		bool nautilusPresent = wxFileName::IsFileExecutable (wxT("/usr/bin/nautilus"));
+		bool xdgOpenPresent = wxFileName::IsFileExecutable (wxT("/usr/bin/xdg-open")) || wxFileName::IsFileExecutable (wxT("/usr/local/bin/xdg-open"));
+		bool nautilusPresent = wxFileName::IsFileExecutable (wxT("/usr/bin/nautilus")) || wxFileName::IsFileExecutable (wxT("/usr/local/bin/nautilus"));
 
 		if (desktop == L"GNOME" || (desktop.empty() && !xdgOpenPresent && nautilusPresent))
 		{
-			args.push_back ("--no-default-window");
+			// args.push_back ("--no-default-window"); // This option causes nautilus not to launch under FreeBSD 11
 			args.push_back ("--no-desktop");
 			args.push_back (string (path));
 			try
