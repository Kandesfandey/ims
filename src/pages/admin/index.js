import React from "react";
import { SideBar, NavBar } from "../../components";
import { Home, HomeContainer } from "../admin/styles/admin";

const Admin = () => {
  return (
    <>
      <Home>
        <SideBar />
        <HomeContainer>
          <NavBar />
        </HomeContainer>
      </Home>
    </>
  );
};

export default Admin;
