<?php

	namespace Proj\Site\Templates\News;

	use Base\Templates\Buffering;
	use Proj\Units\Consts;

	abstract class Show {

		public static function ToVar(array $data): string {
			Buffering::Start();
			self::Render($data);
			return Buffering::Read();
		}

		public static function Render(array $data): void {
			$background = $data['cover'] ? 'style = "background-image: url(' . Consts\News::PATH_COVER_RELATIVE . $data['cover'] . ');"' : '';
		?>
			<div class = "view news show">
				<div class = "cover"<?= $background; ?>>
					<div></div>
					<div class = "grid col_1">
						<div>
							<h1><?= $data['header']; ?></h1>
						</div>
					</div>
				</div>
				<div class = "content"><?= $data['content']; ?></div>
				<div class = "data publish"><?= $data['datepb']; ?></div>
			</div>
		<?php }

	}