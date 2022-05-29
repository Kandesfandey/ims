import React from "react";
import { SideBar, NavBar } from "../../components";
import { HomeContainer, HomeInnerContainer } from "./styles/home";

const Home = () => {
  return (
    <HomeContainer>
      <SideBar />
      <HomeInnerContainer>
        <NavBar />
        {/* <DataTable /> */}
      </HomeInnerContainer>
    </HomeContainer>
  );
};

export default Home;
