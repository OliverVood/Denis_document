<?php

	namespace Proj\Site\Templates\Catalogs;

	use Base\Templates\Template;

	abstract class Estimate {

		public static function ToVar(): string {
			Template::Start();
			self::Render();
			return Template::Read();
		}

		public static function Render(): void { ?>
			<div class = "view catalogs work">
				<h1 class = "glob_print_tabu">Работа со сметами</h1>
				<script>
					let Estimate = new Site.Catalogs.EstimateController('.view.catalogs.work');
				</script>
			</div>
		<?php }

	}