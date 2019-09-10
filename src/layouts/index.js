import { Layout } from 'antd';
import Header from './Header';
import Content from './Content';
import Footer from './Footer';

function BasicLayout({ children, location }) {
  console.log(location.pathname);
  return (
    <Layout>
      <Header location={location} />
      <Content children={children} location={location} />
      <Footer />
    </Layout>
  );
}

export default BasicLayout;
