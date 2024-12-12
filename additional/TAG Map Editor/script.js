document.getElementById('generate-map').addEventListener('click', function() {
    const width = parseInt(document.getElementById('width').value);
    const height = parseInt(document.getElementById('height').value);

    if (isNaN(width) || isNaN(height) || width <= 0 || height <= 0 || width > 100 || height > 100) {
        alert('Please enter valid width and height between from 1 to 100!');
        return;
    }

    const mapGrid = document.getElementById('map-grid');
    mapGrid.innerHTML = '';
    mapGrid.style.gridTemplateColumns = `repeat(${width}, 50px)`;
    mapGrid.style.gridTemplateRows = `repeat(${height}, 50px)`;

    for (let i = 0; i < width * height; i++) {
        const cell = document.createElement('div');
        cell.className = 'cell';
        cell.dataset.building = '100';
        cell.addEventListener('click', function() {
            const selectedBuilding = document.querySelector('.building.selected');
            if (selectedBuilding) {
                cell.dataset.building = selectedBuilding.dataset.building;
                const img = document.createElement('img');
                img.src = selectedBuilding.querySelector('img').src; // Use building image
                img.alt = selectedBuilding.dataset.building;
                cell.innerHTML = '';
                cell.appendChild(img);
            }
        });
        mapGrid.appendChild(cell);
    }
});

document.getElementById('building-list').addEventListener('click', function(event) {
    if (event.target.closest('.building')) {
        document.querySelectorAll('.building').forEach(building => building.classList.remove('selected'));
        event.target.closest('.building').classList.add('selected');
    }
});

document.getElementById('save-map').addEventListener('click', function() {
    const width = document.getElementById('width').value;
    const height = document.getElementById('height').value;
    const mapGrid = document.getElementById('map-grid');
    const cells = mapGrid.querySelectorAll('.cell');

    let mapData = `${height} ${width}\n`;

    cells.forEach(cell => {
        console.log(`Cell data-building: ${cell.dataset.building}`);
    });

    for (let i = 0; i < height; i++) {
        for (let j = 0; j < width; j++) {
            const cell = cells[i * width + j];
            const buildingAttribute = cell.dataset.building === '200' ? '2' : '1';
            mapData += buildingAttribute;
            if (j < width - 1) {
                mapData += ' ';
            }
        }
        mapData += '\n';
    }

    for (let i = 0; i < height; i++) {
        for (let j = 0; j < width; j++) {
            const cell = cells[i * width + j];
            const buildingAttribute = cell.dataset.building;

            const valueToWrite = (buildingAttribute === '100' || buildingAttribute === '200') ? '0' : buildingAttribute;

            mapData += valueToWrite;
            if (j < width - 1) {
                mapData += ' ';
            }
        }
        if (i < height - 1) {
            mapData += '\n';
        }
    }

    const blob = new Blob([mapData], { type: 'text/plain' });
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = 'map.txt';
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);
});