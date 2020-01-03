$(document).ready(async function () {
    async function getEmployeeData() {
        const data = await fetch("/employees");
        const employees = await data.json();
        return employees;
    }

    const generateEmployeeRowTemplate = (employee, i) => {
        const employeeRow = `
             <tr>
              <th scope="row">${i + 1}</th>
              <td>${employee.name}</td>
              <td>${employee.department}</td>
              <td>${employee.gender}</td>
            </tr>
            `
        return employeeRow;
    }

    const tableBodyEl = document.querySelector("tbody");
    const employees = await getEmployeeData();
    employees.forEach((employee, i) => tableBodyEl.insertAdjacentHTML("beforeEnd", generateEmployeeRowTemplate(employee, i)));
});