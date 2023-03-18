<?php

	namespace Proj\Admin\Templates;

	use Base\Templates\View;

	class TemplateAuthorization extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?><!doctype html>
			<html lang  = "ru"<?php LayoutAuthorization::BrowseData(); ?>>
				<head>
					<meta charset = "UTF-8">
					<meta name = "viewport" content = "width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
					<meta http-equiv = "X-UA-Compatible" content = "ie=edge">
					<title>Document</title>
					<?php
						LayoutAuthorization::BrowseHead();
					?>
				</head>
				<body<?php LayoutAuthorization::BrowseData(); ?>>
					<?php $this->RenderSections(); ?>
					<script>
						$(function() {
							//Base.Common.GlobalParams.Set('request', '<?//= \REQUEST; ?>//');
							// Admin.Common.Layout.Initialization();
						});
					</script>
				</body>
			</html>
		<?php }

		public function RenderSections() { ?>
			<header><?php LayoutAuthorization::instance()->header->Browse(); ?></header>
			<main><?php LayoutAuthorization::instance()->main->Browse(); ?></main>
			<footer><?php LayoutAuthorization::instance()->footer->Browse(); ?></footer>
		<?php }

	}