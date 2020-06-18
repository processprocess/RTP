const canvas = document.createElement('canvas');
const ctx = canvas.getContext('2d');
document.body.appendChild(canvas);
const width = (canvas.width = window.innerWidth);
const height = (canvas.height = window.innerHeight);

function circlePoints(numPoints, radius) {
  const slice = (Math.PI * 2) / numPoints;
  const newPoints = [];
  for (let i = 0; i < numPoints; i++) {
    const angle = i * slice;
    const x = radius * Math.cos(angle);
    const y = radius * Math.sin(angle);
    newPoints.push([x, y]);
  }
  return newPoints;
}

const radius = 200;
ctx.translate(width / 2 - 200, height / 2);
let points = circlePoints(5, radius);

ctx.globalCompositeOperation = 'screen';

ctx.translate(-50, -50);
ctx.fillStyle = 'rgba(255,0,0,.02)';
drawDeformedShape(deformShape(points, 2));

ctx.translate(200, 0);
ctx.fillStyle = 'rgba(0,0,255,.02)';
drawDeformedShape(deformShape(points, 2));

ctx.translate(300, 0);
ctx.fillStyle = 'rgba(0,255,0,.02)';
drawDeformedShape(deformShape(points, 2));

function drawDeformedShape(points) {
  var deformedShape = deformShape(points, 3);
  drawShape(deformedShape);
  for (let i = 0; i < 100; i++) {
    drawShape(deformShape(deformedShape));
  }

  function drawShape(points) {
    ctx.beginPath();
    ctx.moveTo(points[0][0], points[0][1]);
    points.forEach((p) => {
      ctx.lineTo(p[0], p[1]);
    });
    ctx.lineTo(points[0][0], points[0][1]);
    ctx.fill();
    return points;
  }
}

// deformedShape = deformShape(deformedShape);
// drawShape(deformedShape);
// deformedShape = deformShape(deformedShape);
// drawShape(deformedShape);
// deformedShape = deformShape(deformedShape);
// drawShape(deformedShape);
// deformedShape = deformShape(deformedShape);
// drawShape(deformedShape);

function deformShape(points, factor = 0) {
  const newPoints = [];
  points.forEach((p, i) => {
    const nextPoint = points[i + 1] ? points[i + 1] : points[0];

    var midX = p[0] + (nextPoint[0] - p[0]) * 0.5;
    var midY = p[1] + (nextPoint[1] - p[1]) * 0.5;

    const midPoint = [
      midX + randomInRange(-30, 30),
      midY + randomInRange(-30, 30),
    ];
    newPoints.push(p);
    newPoints.push(midPoint);
  });
  if (factor === 0) {
    return newPoints;
  } else {
    return deformShape(newPoints, (factor -= 1));
  }
}

function randomInRange(min, max) {
  return map(randn_bm(), -1, 1, 0, 1) * (max - min) + min;
}

console.log(map(randn_bm(), -1, 1, 0, 1));

function randn_bm() {
  var u = 0,
    v = 0;
  while (u === 0) u = Math.random(); //Converting [0,1) to (0,1)
  while (v === 0) v = Math.random();
  return Math.sqrt(-2.0 * Math.log(u)) * Math.cos(2.0 * Math.PI * v);
}

function map(value, x1, y1, x2, y2) {
  return ((value - x1) * (y2 - x2)) / (y1 - x1) + x2;
}
