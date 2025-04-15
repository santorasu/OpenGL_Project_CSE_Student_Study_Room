#include <GL/glut.h>
#include <cmath>
#include <windows.h>
#include <mmsystem.h>

void drawFilledRect(float x, float y, float w, float h);
void drawLine(float x1, float y1, float x2, float y2);
void updateBackground();


float fanAngle = 0.0f; // Rotation angle for the fan
bool isDay = true;
bool lampOn = false; // true = light is ON by default



// -----------------------------------------------------------
// 1. HELPER FUNCTIONS
// -----------------------------------------------------------
void drawCeilingFan() {
    glPushMatrix();
    glTranslatef(0.0f, 60.0f, 0.0f); // Lowered a bit to be visible
    glRotatef(fanAngle, 0.0f, 0.0f, 1.0f);
    glColor3f(0.2f, 0.2f, 0.2f);
    for (int i = 0; i < 3; i++) {
        drawFilledRect(-2.0f, 0.0f, 4.0f, 25.0f);
        glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
    }
    glPopMatrix();

    // Fan Rod
    glColor3f(0.0f, 0.0f, 0.0f);
    drawLine(0.0f, 140.0f, 0.0f, 125.0f);
}

void updateFan(int value) {
    fanAngle += 5.0f; // Speed of rotation
    if (fanAngle >= 360.0f)
        fanAngle -= 360.0f;
    glutPostRedisplay();
    glutTimerFunc(16, updateFan, 0); // 60 FPS
}


void drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawFilledRect(float x, float y, float w, float h)
{
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void drawOutlinedRect(float x, float y, float w, float h)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void drawFilledCircle(float cx, float cy, float r, int segments = 50)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1415926f * i / segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawCircleOutline(float cx, float cy, float r, int segments = 50)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1415926f * i / segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawTrapezoid(float x1, float y1, float x2, float y2,
                   float x3, float y3, float x4, float y4)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

// Helper function to draw an ellipse (filled)
void drawFilledEllipse(float cx, float cy, float rx, float ry, int segments = 50)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1415926f * i / segments;
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void renderBitmapString(float x, float y, void *font, const char *string)
{
    glRasterPos2f(x, y); // Set text position
    while (*string)
    {
        glutBitmapCharacter(font, *string); // Render each character
        string++; // Move to the next character
    }
}

// -----------------------------------------------------------
// 2. SCENE COMPONENTS (Original)
// -----------------------------------------------------------

void drawFloorAndWall()
{
    // Floor (light gray, y: -120 to -80)
    glColor3f(0.92f, 0.92f, 0.92f);
    drawFilledRect(-200.0f, -120.0f, 400.0f, 40.0f);

    // Wall
    glColor3f(211.0f / 255.0f, 211.0f / 255.0f, 211.0f / 255.0f);
    drawFilledRect(-200.0f, -80.0f, 400.0f, 200.0f);
}

void drawWindowWithCurtains()
{
    // Window
   glColor3f(isDay ? 0.8f : 0.0f, isDay ? 0.9f : 0.0f, isDay ? 1.0f : 0.2f); // Blue or dark

    drawFilledRect(-130.0f, 30.0f, 60.0f, 50.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(-130.0f, 30.0f, 60.0f, 50.0f);
    drawLine(-100.0f, 30.0f, -100.0f, 80.0f);
    drawLine(-130.0f, 55.0f, -70.0f, 55.0f);

    // Curtains
    drawLine(-135.0f, 85.0f, -65.0f, 85.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-135.0f, 85.0f);
    glVertex2f(-132.0f, 85.0f);
    glVertex2f(-130.0f, 75.0f);
    glVertex2f(-132.0f, 60.0f);
    glVertex2f(-135.0f, 30.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(-65.0f, 85.0f);
    glVertex2f(-68.0f, 85.0f);
    glVertex2f(-70.0f, 75.0f);
    glVertex2f(-68.0f, 60.0f);
    glVertex2f(-65.0f, 30.0f);
    glEnd();
}
void keyboard(unsigned char key, int x, int y) {
    if (key == 'd' || key == 'D') {
        isDay = !isDay;
        updateBackground();
        glutPostRedisplay();
    }
    else if (key == 'l' || key == 'L') {
        lampOn = !lampOn;
        glutPostRedisplay();
    }
}

// Global variables for animation
float lampX = -10.0f; // Initial position
float speed = 0.1f;   // Movement speed
bool movingRight = true; // Direction flag

void updateLampPosition()
{
    if (movingRight)
    {
        lampX += speed;
        if (lampX >= 10.0f) // Right boundary
            movingRight = false;
    }
    else
    {
        lampX -= speed;
        if (lampX <= -10.0f) // Left boundary
            movingRight = true;
    }

    glutPostRedisplay(); // Request to redraw
}

void drawAnimatedCeilingLamp()
{
    glPushMatrix();              // Save current transformation
    glTranslatef(lampX, 0.0f, 0.0f); // Apply translation for movement

    // Draw lamp components
    glColor3f(0.0f, 0.0f, 0.0f);
    drawLine(0.0f, 140.0f, 0.0f, 110.0f);

    glColor3f(0.7f, 0.7f, 0.7f);
    drawTrapezoid(-10.0f, 110.0f, 10.0f, 110.0f, 16.0f, 100.0f, -16.0f, 100.0f);

    if (lampOn)
    glColor3f(1.0f, 1.0f, 0.8f); // Bright yellow when on
    else
    glColor3f(0.3f, 0.3f, 0.3f); // Dim gray when off

    drawFilledCircle(0.0f, 100.0f, 5.0f);


    glColor3f(0.0f, 0.0f, 0.0f);
    drawTrapezoid(-10.0f, 110.0f, 10.0f, 110.0f, 16.0f, 100.0f, -16.0f, 100.0f);
    drawCircleOutline(0.0f, 100.0f, 5.0f);

    glPopMatrix(); // Restore previous transformation
}

void timer(int)
{
    updateLampPosition();
    glutTimerFunc(16, timer, 0); // Call again in ~16ms (60 FPS)
}

void drawDeskSetup()
{
    // Desk
    glColor3f(0.6f, 0.4f, 0.2f);
    drawFilledRect(-60.0f, -40.0f, 120.0f, 5.0f);
    drawFilledRect(-58.0f, -80.0f, 4.0f, 40.0f);
    drawFilledRect(54.0f, -80.0f, 4.0f, 40.0f);

    // Monitor
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledRect(-25.0f, -20.0f, 50.0f, 25.0f);
    glColor3f(0.4f, 0.4f, 0.4f);
    drawOutlinedRect(-25.0f, -20.0f, 50.0f, 25.0f);
    glColor3f(0.3f, 0.3f, 0.3f);
    drawFilledRect(-2.0f, -40.0f, 4.0f, 5.0f);

    // CPU Tower
    glColor3f(0.4f, 0.4f, 0.4f);
    drawFilledRect(70.0f, -80.0f, 15.0f, 30.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(70.0f, -80.0f, 15.0f, 30.0f);
}

// Global variables for the two clock hands' angles
float fastDialAngle = 0.0f; // Fast-moving dial (e.g., seconds hand)
float slowDialAngle = 0.0f; // Slower-moving dial (e.g., minutes hand)

void drawClockFace()
{
    glColor3f(0.9f, 0.5f, 0.2f);
    drawFilledCircle(150.0f, 80.0f, 12.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(150.0f, 80.0f, 10.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircleOutline(150.0f, 80.0f, 12.0f);
    drawCircleOutline(150.0f, 80.0f, 10.0f);

    // Hour markers
    for (int i = 0; i < 12; i++)
    {
        float angle = 2.0f * 3.1415926f * i / 12.0f;
        float x1 = 150.0f + 9.0f * cosf(angle);
        float y1 = 80.0f + 9.0f * sinf(angle);
        float x2 = 150.0f + 7.0f * cosf(angle);
        float y2 = 80.0f + 7.0f * sinf(angle);
        drawLine(x1, y1, x2, y2);
    }
}

void drawClockHand(float angleDegrees, float handLength)
{
    glPushMatrix();
    glTranslatef(150.0f, 80.0f, 0.0f);
    glRotatef(-angleDegrees - 90.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawLine(0.0f, 0.0f, 0.0f, handLength);
    glPopMatrix();
}

void drawWallClock()
{
    drawClockFace();
    drawClockHand(fastDialAngle, 8.0f);
    drawClockHand(slowDialAngle, 6.0f);
}

void updateClockHands(int value)
{
    fastDialAngle += 1.0f;  // Adjust speed as desired
    slowDialAngle += 0.5f;   // Adjust speed as desired

    if (fastDialAngle >= 360.0f)
        fastDialAngle -= 360.0f;
    if (slowDialAngle >= 360.0f)
        slowDialAngle -= 360.0f;

    glutPostRedisplay();  // Request to redraw the scene
    glutTimerFunc(16, updateClockHands, 0);  // Call again after ~16ms (60 FPS)
}

void drawShelfRight()
{
    glColor3f(0.5f, 0.3f, 0.1f);
    drawFilledRect(170.0f, -20.0f, 20.0f, 60.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(170.0f, -20.0f, 20.0f, 60.0f);

    // Shelf board
    drawLine(170.0f, 10.0f, 190.0f, 10.0f);

    // Decorative items
    glColor3f(0.0f, 0.6f, 0.0f);
    drawFilledRect(172.0f, 12.0f, 4.0f, 8.0f); // pot
    glColor3f(0.0f, 0.8f, 0.0f);
    drawFilledCircle(174.0f, 22.0f, 3.0f);

    glColor3f(0.9f, 0.8f, 0.0f);
    drawFilledRect(182.0f, 12.0f, 4.0f, 8.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(182.0f, 12.0f, 4.0f, 8.0f);
}

void drawBookshelfLeft()
{
    glColor3f(0.5f, 0.3f, 0.1f);
    drawFilledRect(-190.0f, -80.0f, 40.0f, 100.0f);

    // Shelf outlines
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(-190.0f, -80.0f, 40.0f, 100.0f);
    drawLine(-190.0f, -50.0f, -150.0f, -50.0f); // First shelf
    drawLine(-190.0f, -20.0f, -150.0f, -20.0f); // Second shelf
    drawLine(-190.0f, 10.0f, -150.0f, 10.0f);   // Third shelf

    // Books
    glColor3f(1.0f, 0.0f, 0.0f);
    drawFilledRect(-185.0f, -75.0f, 6.0f, 25.0f); // Red book
    glColor3f(0.0f, 0.0f, 1.0f);
    drawFilledRect(-177.0f, -75.0f, 6.0f, 25.0f); // Blue book
    glColor3f(0.0f, 1.0f, 0.0f);
    drawFilledRect(-169.0f, -75.0f, 6.0f, 25.0f); // Green book
    glColor3f(1.0f, 1.0f, 0.0f);
    drawFilledRect(-161.0f, -75.0f, 6.0f, 25.0f); // Yellow book

    // Second shelf
    glColor3f(0.5f, 0.0f, 0.5f);
    drawFilledRect(-185.0f, -45.0f, 6.0f, 25.0f); // Purple book
    glColor3f(0.0f, 0.5f, 0.5f);
    drawFilledRect(-177.0f, -45.0f, 6.0f, 25.0f); // Cyan book
    glColor3f(1.0f, 0.5f, 0.0f);
    drawFilledRect(-169.0f, -45.0f, 6.0f, 25.0f); // Orange book
    glColor3f(0.5f, 0.5f, 0.5f);
    drawFilledRect(-161.0f, -45.0f, 6.0f, 25.0f); // Gray book

    // Third shelf
    glColor3f(0.8f, 0.0f, 0.2f);
    drawFilledRect(-185.0f, -15.0f, 6.0f, 25.0f); // Dark Red book
    glColor3f(0.3f, 0.3f, 1.0f);
    drawFilledRect(-177.0f, -15.0f, 6.0f, 25.0f); // Light Blue book
    glColor3f(0.2f, 0.6f, 0.2f);
    drawFilledRect(-169.0f, -15.0f, 6.0f, 25.0f); // Dark Green book
    glColor3f(0.9f, 0.7f, 0.1f);
    drawFilledRect(-161.0f, -15.0f, 6.0f, 25.0f); // Gold book
}

void drawKeyboardOnTable()
{
    // Set the keyboard base color (light gray)
    glColor3f(0.8f, 0.8f, 0.8f);

    // Keyboard dimensions: width = 30, height = 4.
    float keyboardWidth = 30.0f;
    float keyboardHeight = 4.0f;
    float tableCenterX = 0.0f;
    // Updated y coordinate: raised to -34.5
    float keyboardY = -34.5f;

    // Calculate bottom-left coordinate so the keyboard is centered on the table.
    float keyboardX = tableCenterX - keyboardWidth / 2.0f;

    // Draw the keyboard base
    drawFilledRect(keyboardX, keyboardY, keyboardWidth, keyboardHeight);

    // Draw the outline of the keyboard base
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(keyboardX, keyboardY, keyboardWidth, keyboardHeight);

    // ----- Draw Keys on the Keyboard -----
    int rows = 3, cols = 10;
    float keyPadding = 0.5f;
    float keyWidth = (keyboardWidth - (cols + 1) * keyPadding) / cols;
    float keyHeight = (keyboardHeight - (rows + 1) * keyPadding) / rows;

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            // Compute the x and y position for each key
            float keyX = keyboardX + keyPadding + col * (keyWidth + keyPadding);
            float keyY = keyboardY + keyPadding + row * (keyHeight + keyPadding);

            // Fill key with a slightly darker shade to differentiate from the base
            glColor3f(0.7f, 0.7f, 0.7f);
            drawFilledRect(keyX, keyY, keyWidth, keyHeight);

            // Outline the key
            glColor3f(0.0f, 0.0f, 0.0f);
            drawOutlinedRect(keyX, keyY, keyWidth, keyHeight);
        }
    }
}

// Function to draw a mouse on the table, placed to the right of the keyboard.
void drawMouseOnTable()
{
    float mouseWidth = 10.0f;
    float mouseHeight = 3.0f;
    float mouseX = 17.0f;
    float mouseY = -34.5f;

    float mouseCenterX = mouseX + mouseWidth / 2.0f;
    float mouseCenterY = mouseY + mouseHeight / 2.0f;
    float radiusX = mouseWidth / 2.0f;
    float radiusY = mouseHeight / 2.0f;
    glColor3f(0.2f, 0.2f, 0.2f);

    drawFilledEllipse(mouseCenterX, mouseCenterY, radiusX, radiusY);

    glColor3f(0.5f, 0.5f, 0.5f);
    drawFilledCircle(mouseCenterX, mouseCenterY, 0.5f);
}
void drawToDoListBoard() {
    // Add the definition here (as you did earlier)
    // Define board position and size
    float boardX = 70.0f;
    float boardY = 15.0f;
    float boardWidth = 50.0f;
    float boardHeight = 60.0f;

    // ----- Draw Wooden Border -----
    glColor3f(0.5f, 0.3f, 0.1f);
    drawFilledRect(boardX - 2, boardY - 2, boardWidth + 4, boardHeight + 4);

    // ----- Draw White Board Surface -----
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledRect(boardX, boardY, boardWidth, boardHeight);

    // ----- Draw Outline -----
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(boardX, boardY, boardWidth, boardHeight);

    // ----- Display Tasks -----
    glColor3f(0.0f, 0.0f, 0.0f);
    float textX = boardX + 5.0f;
    float textY = boardY + boardHeight - 10.0f;

    renderBitmapString(textX, textY, GLUT_BITMAP_HELVETICA_12, "To-Do List:");
    renderBitmapString(textX, textY - 15, GLUT_BITMAP_HELVETICA_12, "- Computer Graphics Project");
    renderBitmapString(textX, textY - 30, GLUT_BITMAP_HELVETICA_12, "- Computer Graphics Lab");
    renderBitmapString(textX, textY - 45, GLUT_BITMAP_HELVETICA_12, "- Computer Graphics Quiz");
}

void drawLeftSpeaker() {
    // Add the definition here (as you did earlier)
    glColor3f(0.3f, 0.3f, 0.3f); // Dark gray

    // Main body (15w x 25h)
    drawFilledRect(-75.0f, -80.0f, 15.0f, 25.0f);

    // Speaker details (properly spaced)
    glColor3f(0.1f, 0.1f, 0.1f);
    drawFilledCircle(-70.0f, -65.0f, 2.0f);  // Woofer (left)
    drawFilledCircle(-65.0f, -65.0f, 2.0f);  // Tweeter (right)

    // Base
    glColor3f(0.4f, 0.4f, 0.4f);
    drawFilledRect(-75.0f, -80.0f, 15.0f, 3.0f);

    // Outline
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(-75.0f, -80.0f, 15.0f, 25.0f);
}

void drawSeat() {
    // ---- Seat Cushion ----
    float seatX = -40.0f;
    float seatY = -60.0f;
    float seatWidth = 80.0f;
    float seatHeight = 15.0f;

    glColor3f(0.7f, 0.5f, 0.3f);
    drawFilledRect(seatX, seatY, seatWidth, seatHeight);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(seatX, seatY, seatWidth, seatHeight);

    // ---- Backrest ----
    float backrestHeight = 15.0f;
    glColor3f(0.7f, 0.5f, 0.3f);
    drawFilledRect(seatX, seatY - backrestHeight, seatWidth, backrestHeight);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(seatX, seatY - backrestHeight, seatWidth, backrestHeight);

    // ---- Seat Legs ----
    float legWidth = 8.0f;
    float legHeight = 20.0f;

    glColor3f(0.5f, 0.3f, 0.1f);
    drawFilledRect(seatX + 5.0f, seatY - legHeight, legWidth, legHeight);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(seatX + 5.0f, seatY - legHeight, legWidth, legHeight);

    glColor3f(0.5f, 0.3f, 0.1f);
    drawFilledRect(seatX + seatWidth - 5.0f - legWidth, seatY - legHeight, legWidth, legHeight);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutlinedRect(seatX + seatWidth - 5.0f - legWidth, seatY - legHeight, legWidth, legHeight);
}
void drawWallPainting() {
    glColor3f(0.8f, 0.2f, 0.0f); // Frame color (brown)
    drawFilledRect(60.0f, 80.0f, 40.0f, 30.0f); // Frame

    glColor3f(0.1f, 0.1f, 0.1f); // Inside painting color (dark)
    drawFilledRect(65.0f, 85.0f, 30.0f, 20.0f); // Painting surface
}
void drawCoffeeMug() {
    float x = -30.0f;
    float y = -34.5f;
    float mugW = 7.0f;
    float mugH = 10.0f;
    float topCenterX = x + mugW / 2.0f;
    float topY = y + mugH;

    // Mug body
    glColor3f(0.6f, 0.3f, 0.1f); // Coffee brown
    drawFilledRect(x, y, mugW, mugH);

    // Mug top (ellipse opening)
    glColor3f(0.8f, 0.5f, 0.2f); // Slightly lighter rim
    drawFilledEllipse(topCenterX, topY, mugW / 2.0f, 1.5f);

    // Handle (perfect rounded loop on right side)
    glColor3f(0.6f, 0.3f, 0.1f);
    glBegin(GL_LINE_STRIP);
    for (float angle = -3.14f / 2; angle <= 3.14f / 2; angle += 0.1f) {
        float radius = 4.0f;
        float handleX = x + mugW + cosf(angle) * 2.5f;
        float handleY = y + mugH / 2.0f + sinf(angle) * 4.0f;
        glVertex2f(handleX, handleY);
    }
    glEnd();
}

void drawWallCalendar() {
    // Lower position (left-bottom wall)
    float x = -120.0f;
    float y = -20.0f;
    float w = 60.0f;
    float h = 40.0f;

    // Frame
    glColor3f(0.6f, 0.1f, 0.1f); // Dark red
    drawFilledRect(x, y, w, h);

    // Inner sheet
    glColor3f(1.0f, 1.0f, 1.0f); // White area
    drawFilledRect(x + 4, y + 4, w - 8, h - 8);

    // Header (month label)
    glColor3f(0.0f, 0.0f, 0.0f);
    renderBitmapString(x + 10.0f, y + h - 10.0f, GLUT_BITMAP_HELVETICA_12, "April 2025");

    // Draw 7x5 grid for days
    float gridX = x + 6.0f;
    float gridY = y + 6.0f;
    float gridW = w - 12.0f;
    float gridH = h - 20.0f;
    int cols = 7, rows = 5;

    float cellW = gridW / cols;
    float cellH = gridH / rows;

    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= rows; i++) {
        drawLine(gridX, gridY + i * cellH, gridX + gridW, gridY + i * cellH); // horizontal lines
    }
    for (int j = 0; j <= cols; j++) {
        drawLine(gridX + j * cellW, gridY, gridX + j * cellW, gridY + gridH); // vertical lines
    }
}

void drawFlooringBed() {
    // Bed position and size, moved further to the right for a darker area
    float bedX = 100.0f;        // X position (to move it more right)
    float bedY = -80.0f;       // Y position (on the floor)
    float bedWidth = 90.0f;     // Bed width
    float bedHeight = 12.0f;    // Bed platform height (thin)

    // Bed platform (Wooden color for the bed's base)
    glColor3f(0.4f, 0.2f, 0.0f); // Dark brown wood color
    drawFilledRect(bedX, bedY, bedWidth, bedHeight);

    // Mattress (Light color for the soft mattress)
    glColor3f(0.7f, 0.9f, 1.0f); // Light blue for the mattress
    drawFilledRect(bedX + 3, bedY + 3, bedWidth - 6, bedHeight - 6);

    // Pillow (White color)
    glColor3f(1.0f, 1.0f, 1.0f); // White for the pillow
    drawFilledRect(bedX + bedWidth - 20.0f, bedY + bedHeight - 8.0f, 15.0f, 6.0f); // Pillow at the edge

    // Blanket (Optional, light pink for the blanket)
    glColor3f(0.8f, 0.6f, 0.7f); // Light pink for blanket
    drawFilledRect(bedX + 5.0f, bedY + 3.0f, 50.0f, bedHeight - 6.0f); // Blanket slightly folded
}




// -----------------------------------------------------------
// 4. DISPLAY FUNCTION
// -----------------------------------------------------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawFloorAndWall();
    drawFlooringBed();
    drawWindowWithCurtains();
    drawAnimatedCeilingLamp();
    drawDeskSetup();
    drawWallClock();
    drawShelfRight();
    drawBookshelfLeft();
    drawToDoListBoard();
    drawLeftSpeaker();
    drawKeyboardOnTable();
    drawMouseOnTable();
    drawSeat();
    drawCeilingFan();
    drawCoffeeMug();
drawWallCalendar();

    glutSwapBuffers();

}


// -----------------------------------------------------------
// 5. INIT & MAIN
// -----------------------------------------------------------
void updateBackground() {
    if (isDay)
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White for day
    else
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Dark blue for night

    glutPostRedisplay();
}

void init()
{

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200.0, 200.0, -120.0, 120.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(2.0f);
     updateBackground();
}



int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("Computer Science Student Room");
    glutFullScreen();
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(16, updateClockHands, 0);
    PlaySound(TEXT("ss.wav"), NULL, SND_FILENAME | SND_ASYNC);
     glutKeyboardFunc(keyboard);
    glutTimerFunc(0, updateFan, 0);
    glutMainLoop();
    return 0;
}
