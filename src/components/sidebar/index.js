import React from "react";
import DashboardIcon from "@mui/icons-material/Dashboard";
import PersonOutlineIcon from "@mui/icons-material/PersonOutline";
import LocalShippingIcon from "@mui/icons-material/LocalShipping";
import CreditCardIcon from "@mui/icons-material/CreditCard";
import StoreIcon from "@mui/icons-material/Store";
import InsertChartIcon from "@mui/icons-material/InsertChart";
import SettingsApplicationsIcon from "@mui/icons-material/SettingsApplications";
import ExitToAppIcon from "@mui/icons-material/ExitToApp";
import NotificationsNoneIcon from "@mui/icons-material/NotificationsNone";
import SettingsSystemDaydreamOutlinedIcon from "@mui/icons-material/SettingsSystemDaydreamOutlined";
import PsychologyOutlinedIcon from "@mui/icons-material/PsychologyOutlined";
import AccountCircleOutlinedIcon from "@mui/icons-material/AccountCircleOutlined";
import { Link } from "react-router-dom";
import {
  SidebarContainer,
  TopContainer,
  LinkContainer,
  Logo,
  Divider,
  CenterContainer,
  UnorderedList,
  Title,
  ListElement,
  SpanContainer,
} from "./styles/sidebar";

const SideBar = () => {
  return (
    <SidebarContainer>
      <TopContainer>
        <LinkContainer to="/">
          <Logo>lamadmin</Logo>
        </LinkContainer>
      </TopContainer>
      <Divider />
      <CenterContainer>
        <UnorderedList>
          <Title>MAIN</Title>
          <ListElement>
            <DashboardIcon className="icon" />
            <SpanContainer>Dashboard</SpanContainer>
          </ListElement>
          <Title>LISTS</Title>
          <Link to="/users" style={{ textDecoration: "none" }}>
            <ListElement>
              <PersonOutlineIcon className="icon" />
              <SpanContainer>Users</SpanContainer>
            </ListElement>
          </Link>
          <Link to="/products" style={{ textDecoration: "none" }}>
            <ListElement>
              <StoreIcon className="icon" />
              <SpanContainer>Products</SpanContainer>
            </ListElement>
          </Link>
          <ListElement>
            <CreditCardIcon className="icon" />
            <SpanContainer>Orders</SpanContainer>
          </ListElement>
          <ListElement>
            <LocalShippingIcon className="icon" />
            <SpanContainer>Delivery</SpanContainer>
          </ListElement>
          <Title>USEFUL</Title>
          <ListElement>
            <InsertChartIcon className="icon" />
            <SpanContainer>Stats</SpanContainer>
          </ListElement>
          <ListElement>
            <NotificationsNoneIcon className="icon" />
            <SpanContainer>Notifications</SpanContainer>
          </ListElement>
          <Title>SERVICE</Title>
          <ListElement>
            <SettingsSystemDaydreamOutlinedIcon className="icon" />
            <SpanContainer>System Health</SpanContainer>
          </ListElement>
          <ListElement>
            <PsychologyOutlinedIcon className="icon" />
            <SpanContainer>Logs</SpanContainer>
          </ListElement>
          <ListElement>
            <SettingsApplicationsIcon className="icon" />
            <SpanContainer>Settings</SpanContainer>
          </ListElement>
          <Title>USER</Title>
          <ListElement>
            <AccountCircleOutlinedIcon className="icon" />
            <SpanContainer>Profile</SpanContainer>
          </ListElement>
          <ListElement>
            <ExitToAppIcon className="icon" />
            <SpanContainer>Logout</SpanContainer>
          </ListElement>
        </UnorderedList>
      </CenterContainer>
    </SidebarContainer>
  );
};

export default SideBar;
