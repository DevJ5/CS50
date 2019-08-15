var arr = [6, 2, 1, 3, 5, 4]; // Sorteer van hoog naar laag.

// selection sort
const selectionSort = (arr) => {
    for (let i = 0; i < arr.length - 1; i++) {
        let maxIndex = i;
        for (let j = i + 1; j < arr.length; j++) {
            if (arr[maxIndex] < arr[j]) {
                maxIndex = j;
            }
        }

        swap(arr, i, maxIndex);
    }
}

function swap(arr, i, maxIndex) {
    let temp = arr[i];
    arr[i] = arr[maxIndex];
    arr[maxIndex] = temp;
}

selectionSort(arr);
console.log(arr);