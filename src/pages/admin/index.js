import React from "react";
import { SideBar, NavBar, DataTable } from "../../components";
import { Home, HomeContainer } from "../admin/styles/admin";

const Admin = () => {
  return (
    <>
      <Home>
        <SideBar />
        <HomeContainer>
          <NavBar />
          <DataTable />
        </HomeContainer>
      </Home>
    </>
  );
};

export default Admin;
