import React, { useState } from "react";
import { Link } from "react-router-dom";
import {
  DataTableContainer,
  DataTableTitle,
  DataTableLink,
  CellAction,
  ViewButton,
  DeleteButton,
  CellWithImage,
  CellImage,
  CellWithStatus,
} from "./styles/datatables";
import { DataGrid } from "@mui/x-data-grid";

const userColumns = [
  { field: "id", headerName: "ID", width: 70 },
  {
    field: "user",
    headerName: "Item",
    width: 230,
    renderCell: (params) => {
      return (
        <CellWithImage>
          <CellImage src={params.row.img} alt="avatar" />
          {params.row.name}
        </CellWithImage>
      );
    },
  },
  {
    field: "email",
    headerName: "Email",
    width: 230,
  },

  {
    field: "quantity",
    headerName: "Quantity",
    width: 100,
  },
  {
    field: "status",
    headerName: "Status",
    width: 160,
    renderCell: (params) => {
      return (
        <CellWithStatus className={`${params.row.status}`}>
          {params.row.status}
        </CellWithStatus>
      );
    },
  },
];

//temporary data
const userRows = [
  {
    id: 1,
    name: "Snow",
    img: "https://images.pexels.com/photos/1820770/pexels-photo-1820770.jpeg?auto=compress&cs=tinysrgb&dpr=2&w=500",
    status: "active",
    email: "1snow@gmail.com",
    quantity: 35,
  },
  {
    id: 2,
    name: "Jamie Lannister",
    img: "https://images.pexels.com/photos/1820770/pexels-photo-1820770.jpeg?auto=compress&cs=tinysrgb&dpr=2&w=500",
    email: "2snow@gmail.com",
    status: "passive",
    quantity: 42,
  },
  {
    id: 3,
    name: "Lannister",
    img: "https://images.pexels.com/photos/1820770/pexels-photo-1820770.jpeg?auto=compress&cs=tinysrgb&dpr=2&w=500",
    email: "3snow@gmail.com",
    status: "pending",
    quantity: 45,
  },
  {
    id: 4,
    name: "Stark",
    img: "https://images.pexels.com/photos/1820770/pexels-photo-1820770.jpeg?auto=compress&cs=tinysrgb&dpr=2&w=500",
    email: "4snow@gmail.com",
    status: "active",
    quantity: 16,
  },
  {
    id: 5,
    name: "Targaryen",
    img: "https://images.pexels.com/photos/1820770/pexels-photo-1820770.jpeg?auto=compress&cs=tinysrgb&dpr=2&w=500",
    email: "5snow@gmail.com",
    status: "passive",
    quantity: 22,
  },
  {
    id: 6,
    name: "Melisandre",
    img: "https://images.pexels.com/photos/1820770/pexels-photo-1820770.jpeg?auto=compress&cs=tinysrgb&dpr=2&w=500",
    email: "6snow@gmail.com",
    status: "active",
    quantity: 15,
  },
  {
    id: 7,
    name: "Clifford",
    img: "https://images.pexels.com/photos/1820770/pexels-photo-1820770.jpeg?auto=compress&cs=tinysrgb&dpr=2&w=500",
    email: "7snow@gmail.com",
    status: "passive",
    quantity: 44,
  },
  {
    id: 8,
    name: "Frances",
    img: "https://images.pexels.com/photos/1820770/pexels-photo-1820770.jpeg?auto=compress&cs=tinysrgb&dpr=2&w=500",
    email: "8snow@gmail.com",
    status: "active",
    quantity: 36,
  },
  {
    id: 9,
    name: "Roxie",
    img: "https://images.pexels.com/photos/1820770/pexels-photo-1820770.jpeg?auto=compress&cs=tinysrgb&dpr=2&w=500",
    email: "snow@gmail.com",
    status: "pending",
    quantity: 65,
  },
  {
    id: 10,
    name: "Roxie",
    img: "https://images.pexels.com/photos/1820770/pexels-photo-1820770.jpeg?auto=compress&cs=tinysrgb&dpr=2&w=500",
    email: "snow@gmail.com",
    status: "active",
    quantity: 65,
  },
];

const DataTable = () => {
  const [data, setData] = useState(userRows);

  const handleDelete = (id) => {
    setData(data.filter((item) => item.id !== id));
  };

  const actionColumn = [
    {
      field: "action",
      headerName: "Action",
      width: 200,
      renderCell: (params) => {
        return (
          <CellAction>
            <Link
              to={"/items/" + params.row.id}
              style={{ textDecoration: "none" }}
            >
              <ViewButton>View</ViewButton>
            </Link>
            <DeleteButton onClick={() => handleDelete(params.row.id)}>
              Delete
            </DeleteButton>
          </CellAction>
        );
      },
    },
  ];
  return (
    <DataTableContainer>
      <DataTableTitle>
        Items
        <DataTableLink to="/items/new">Add New</DataTableLink>
      </DataTableTitle>
      <DataGrid
        rows={data}
        columns={userColumns.concat(actionColumn)}
        pageSize={9}
        rowsPerPageOptions={[9]}
        checkboxSelection
      />
    </DataTableContainer>
  );
};

export default DataTable;
