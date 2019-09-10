import { Layout, Menu } from 'antd';

import styles from './styles.css';

const { Header } = Layout;

export default function({ location }) {
  let selected = location.pathname.split('/')[1] || 'home';
  return (
    <Header className={styles.header}>
      <Menu className={styles.nav} theme="light" mode="horizontal" defaultSelectedKeys={[selected]}>
        <Menu.Item key="home" className={styles.home}>
          <a href="/">rluu.dev</a>
        </Menu.Item>
        <Menu.Item key="blog">
          <a href="blog">/blog</a>
        </Menu.Item>
        <Menu.Item key="sketches">
          <a href="sketches">/sketches</a>
        </Menu.Item>
        <Menu.Item key="projects">
          <a href="projects">/projects</a>
        </Menu.Item>
      </Menu>
    </Header>
  );
};
