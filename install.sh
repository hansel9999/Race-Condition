#!/bin/bash

APP_NAME="racecond"
EXECUTABLE_PATH="/usr/local/bin/$APP_NAME"
DESKTOP_FILE="$APP_NAME.desktop"
ICON_FILE="$APP_NAME.png"
ICON_DEST="/usr/share/icons/hicolor/512x512/apps"
DESKTOP_DEST="/usr/share/applications"

# Check for the -d flag to uninstall
if [ "$1" == "-r" ]; then
    echo "Uninstalling $APP_NAME..."
    # Remove the executable
    if [ -f "$EXECUTABLE_PATH" ]; then
        echo "Removing executable..."
        rm -f "$EXECUTABLE_PATH"
    else
        echo "Executable not found, skipping."
    fi
    # Remove the .desktop file
    if [ -f "$DESKTOP_DEST/$DESKTOP_FILE" ]; then
        echo "Removing .desktop file..."
        rm -f "$DESKTOP_DEST/$DESKTOP_FILE"
    else
        echo ".desktop file not found, skipping."
    fi
    # Remove the icon
    if [ -f "${ICON_DEST}/${ICON_FILE}" ]; then
        echo "Removing icon..."
        rm -f "${ICON_DEST}/${ICON_FILE}"
    else
        echo "Icon not found, skipping."
    fi
    # Update desktop database
    echo "Updating desktop database..."
    update-desktop-database "$DESKTOP_DEST"
    echo "Finished"
    exit 0
fi

# Build the executable
echo "Building the application..."
make
# Install the executable
echo "Copying executable to $EXECUTABLE_PATH..."
cp "$APP_NAME" "$EXECUTABLE_PATH"
chmod +x "$EXECUTABLE_PATH"
#Clean build environment
echo "Cleaning up..."
make clean
# Copy the .desktop file
echo "Copying the .desktop file to $DESKTOP_DEST..."
cp "$DESKTOP_FILE" "$DESKTOP_DEST"
# Copy the icon file
echo "Copying the icon to $ICON_DEST..."
mkdir -p "$ICON_DEST"
cp "$ICON_FILE" "$ICON_DEST"
# Update desktop database
echo "Updating desktop database..."
update-desktop-database "$DESKTOP_DEST"
echo "Finished"
