#include <Arduino.h>
#include <BleAbsMouse.h>

#define MINUTE 60000

BleAbsMouse bleAbsMouse("DroChill Mouse Jiggler v1");

int move_interval = 12; // with lower interval notify(): << esp_ble_gatts_send_notify: rc=-1 Unknown ESP_ERR error appears
int loop_interval = MINUTE * 1;

// Absolute mouse positioning variables (0-10000 range)
uint16_t current_x = 5000; // Start at center
uint16_t current_y = 5000; // Start at center
uint16_t min_move = 30;
uint16_t max_move = 600;

void setup() {
  bleAbsMouse.begin();
}

void loop() {
  if (bleAbsMouse.isConnected()) {
    int distance = random(min_move, max_move);
    int x_dir = random(3) - 1; // -1, 0, or 1
    int y_dir = random(3) - 1; // -1, 0, or 1
    
    // Simulate movement by updating absolute position incrementally
    for (int i = 0; i < distance; i++) {
      // Update position, keeping within bounds (0-10000)
      current_x = constrain(current_x + x_dir, 0, 10000);
      current_y = constrain(current_y + y_dir, 0, 10000);
      
      bleAbsMouse.move(current_x, current_y);
      delay(move_interval);
    }
    
    // Random right click
    if (random(0, 7) == 3) {
      bleAbsMouse.click(current_x, current_y);
    }
    
    // Release after movement
    bleAbsMouse.release();
  }
  
  delay(loop_interval);
}
