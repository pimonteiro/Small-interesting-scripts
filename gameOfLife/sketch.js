let cols;
let rows;
let resolution = 20;
let grid;
let MIN_CELL = 2;
let MAX_CELL = 3;
let flag = false;

function make2DArray(cols, rows) {
  let arr = new Array(cols);
  for (let i = 0; i < arr.length; i++) {
    arr[i] = new Array(rows);
  }
  return arr;
}

let bt_start;
let bt_end;
let bt_clear;
let speed_slider;

function setup() {
  createCanvas(800,600);
  speed_slider = createSlider(1,60, 3, 1);
  frameRate(3);

  bt_start = createButton('start');
  bt_end = createButton('stop');
  bt_clear = createButton('clear');

  bt_start.mousePressed(function() {
    flag = true;
  });
  bt_end.mousePressed(function() {
    flag = false;
  });
  bt_clear.mousePressed(function() {
    for(let i = 0; i < cols; i++){
      for(let j = 0; j < rows; j++)
        grid[i][j] = 0;
    }
    flag = false;
  });

  
  cols = width / resolution;
  rows = height / resolution;

  //Create grid
  grid = make2DArray(cols,rows);
  //Populate the intial image
  grid[4][4] = 1;
  grid[5][5] = 1;
  grid[4][5] = 1;
  grid[5][3] = 1;
  grid[4][2] = 1;
  grid[5][6] = 1;

  for(let i = 0; i < cols; i++){
    for(let j = 0; j < rows; j++){
      grid[i][j] = floor(random(2));
    }
  }
}

function draw() {
  background(216,216,216);
  

  frameRate(speed_slider.value());
  for(let i = 0; i < cols; i++){
    for(let j = 0; j < rows; j++){
      let x = i * resolution;
      let y = j * resolution;
      if(grid[i][j]) {
        fill(255, 0, 0);
      }
      else {
        fill(216,216,216)
      }
      stroke(0,0,0);
      strokeWeight(1);
      rect(x,y,resolution-1, resolution-1);
    }
  }

  if(flag){
    let newGrid = make2DArray(cols, rows);
  
    for(let i = 0; i < cols; i++){
      for(let j = 0; j < rows; j++){
        let state = grid[i][j];
        // Count live neighbors!
        let neighbors = countNeighbors(grid, i, j);
  
        if (state == 0 && neighbors == 3) {
          newGrid[i][j] = 1;
        } else if (state == 1 && (neighbors < 2 || neighbors > 3)) {
          newGrid[i][j] = 0;
        } else {
          newGrid[i][j] = state;
        } 
      }
    }
    grid = newGrid;  
  }
}

function mousePressed(){
  let ix = mouseX;
  let iy = mouseY;

  let x = (ix/resolution|0);
  let y = (iy/resolution|0);

  grid[x][y] = 1 - grid[x][y];
  flag = false;
}


function countNeighbors(grid,x,y) {
  let sum = 0;
  for(let i = -1; i < 2; i++){
    for(let j = -1; j < 2; j++){
      let col = (x+i+cols) % cols;
      let row = (y+j+rows) % rows;
      sum += grid[col][row];
    }
  }
  sum -= grid[x][y];
  return sum;
}


