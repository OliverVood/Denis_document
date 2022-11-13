<?php

	namespace Proj\Site\Templates;

	use Base\Templates\View;

	class Template extends View {

	public function ToVar(): string {
		$this->Start();
		$this->Render();
		return $this->Read();
	}

	public function Render() { ?><!doctype html>
			<html lang  = "ru">
				<head>
					<meta charset = "UTF-8">
					<meta name = "viewport" content = "width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
					<meta http-equiv = "X-UA-Compatible" content = "ie=edge">
					<title>Document</title>
					<?php
						Layout::BrowseScripts();
						Layout::BrowseStylesheets();
					?>
				</head>
				<body>
					<? $this->RenderSections(); ?>
					<script>
						let $ui_menu;
						$(function() {
							Base.Common.GlobalParams.Set('request', '<?= \REQUEST; ?>');
							Site.Common.Layout.Initialization();
							$ui_menu = new Site.Common.Menu();
						});
					</script>
				</body>
			</html>
		<?php }

		public function RenderSections() { ?>
			<header><?php Layout::instance()->header->Browse(); ?></header>
			<main>
				<div>
					<?php Layout::instance()->main->Browse(); ?>
				</div>
			</main>
			<footer><?php Layout::instance()->footer->Browse(); ?></footer>
		<?php }

	}