<?php

	namespace Proj\Site\Templates\Catalogs;

	use Base\Templates\Template;

	abstract class PriceList {

		public static function ToVar(): string {
			Template::Start();
			self::Render();
			return Template::Read();
		}

		public static function Render(): void { ?>
			<div class = "view catalogs work">
				<h1 class = "glob_print_tabu">Работа с прайс-листами</h1>
				<script>
					let PriceList = new Site.Catalogs.PriceListController('.view.catalogs.work');
				</script>
			</div>
		<?php }

	}